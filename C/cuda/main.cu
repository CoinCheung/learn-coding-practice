
#include<iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include<cuda_runtime.h>


using std::cout;
using std::endl;
using std::vector;



template<typename scalar_t>
__global__ void compute_square(const int num, const scalar_t* data, scalar_t* res, float* time) {
    clock_t start = clock();
    const int tid = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;
    for (int i{tid}; i < num; i+=stride) {
        res[i] = data[i] * data[i];
    }

    clock_t finish = clock();
    if (tid < num) {
        time[tid] = (float)(finish - start) / CLOCKS_PER_SEC;
    }
}


template<typename scalar_t>
__global__ void compute_sum(const int num, const scalar_t* data, scalar_t* sum) {
    // dynamic allocated
    extern __shared__ __align__(sizeof(scalar_t)) int shared_raw[]; 
    scalar_t *shared = reinterpret_cast<scalar_t*>(shared_raw);
    shared[threadIdx.x] = 0; // assign 0 to the aligned memory
    __syncthreads();

    const int tid = threadIdx.x + blockIdx.x * blockDim.x;
    if (tid < num) {
        shared[threadIdx.x] = data[tid];
    }
    __syncthreads();

    /* int mask = 1, offset = 1;
     * while (offset < blockDim.x) {
     *     if ((tid & mask) == 0) {
     *         shared[threadIdx.x] += shared[threadIdx.x + offset];
     *     }
     *     offset += offset;
     *     mask += offset;
     *     __syncthreads();
     * } */

    // same as above
    for (int s=1; s < blockDim.x; s*=2) {
        int idx = 2 * s * threadIdx.x;
        if (idx < blockDim.x) {
            shared[idx] += shared[idx + s];
        }
        __syncthreads();
    }

    // faster: but only support blockdim is 2**x
    /* for (unsigned int s{blockDim.x / 2}; s > 0; s>>=1) { */
    /*     int idx = threadIdx.x; */
    /*     if (idx < s) { */
    /*         shared[idx] += shared[idx + s]; */
    /*     } */
    /*     __syncthreads(); */
    /* } */

    if (threadIdx.x == 1) { // must be one thread, or will be added many times
        atomicAdd(sum, shared[0]);
    }
}


void check_gpu_info(int device_id) {
    int dev = device_id;
    cudaDeviceProp devProp;
    if (cudaGetDeviceProperties(&devProp, dev)) {
        std::cout << "get properties fail" << std::endl;
        return;
    }
    cout << "device " << dev << ": " << devProp.name << endl;
    cout << "num of SM: " << devProp.multiProcessorCount << endl;
    cout << "shared memory of each block: " 
        << devProp.sharedMemPerBlock
        << endl;
    cout << "max thread num of each block: "
        << devProp.maxThreadsPerBlock
        << endl;
    cout << "max thread num of each SM: "
        << devProp.maxThreadsPerMultiProcessor
        << endl;
    cout << "max thread wrap num of each SM: "
        << devProp.maxThreadsPerMultiProcessor / 32
        << endl;

}

bool InitCUDA() {
    int count;
    cudaGetDeviceCount(&count);
    if (count == 0) {cout << "no gpu device\n"; return false;}
    for (int i{0}; i < count; ++i) {
        check_gpu_info(i);
    }
    cudaSetDevice(0);
    return true;
}


void test_cuda_sync() {
    cout << "test sync" << endl;
    int len{1000};
    vector<float> data(len);
    vector<float> res(len); 
    vector<float> time(len);
    float sum{0};
    std::iota(data.begin(), data.end(), 0);

    // allocate memory
    float *dev_data{nullptr}, *dev_res{nullptr}, *dev_time{nullptr};
    float *dev_sum{nullptr};
    cudaMalloc((void**)&dev_data, sizeof(float) * len);
    cudaMalloc((void**)&dev_res, sizeof(float) * len);
    cudaMalloc((void**)&dev_time, sizeof(float) * len);
    cudaMalloc((void**)&dev_sum, sizeof(float));

    // copy data to device
    cudaMemcpy(dev_data, data.data(), sizeof(float) * len, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_sum, &sum, sizeof(float), cudaMemcpyHostToDevice);

    // execute kernel function
    dim3 block(512);
    dim3 grid(std::min(4096, (int)std::ceil(len / 512.))); 
    compute_square<float><<<grid, block, 4096>>>(len, dev_data, dev_res, dev_time);
    compute_sum<float><<<grid, block, 4096>>>(len, dev_data, dev_sum);

    /// test double type when instantiate template with two types
    // 1. must add compilation option of -arch=sm_60 to support double
    // 2. if to use dynamic shared memory, take care of its declaration
    vector<double> datad(len);
    vector<double> resd(len);
    double *dev_datad{nullptr};
    double *dev_sumd{nullptr};
    cudaMalloc((void**)&dev_datad, sizeof(double) * len);
    cudaMalloc((void**)&dev_sumd, sizeof(double));
    compute_sum<double><<<grid, block, 4096>>>(len, dev_datad, dev_sumd);

    // copy results back to host
    cudaMemcpy(&res[0], dev_res, sizeof(int) * len, cudaMemcpyDeviceToHost);
    cudaMemcpy(&time[0], dev_time, sizeof(float) * len, cudaMemcpyDeviceToHost);
    cudaMemcpy(&sum, dev_sum, sizeof(int), cudaMemcpyDeviceToHost);
    vector<int> tmp_cpu(len);

    // free allocated memory
    cudaFree(dev_data);
    cudaFree(dev_res);
    cudaFree(dev_time);
    cudaFree(dev_sum);

    // check results
    cout << "cuda reduce sum is: \n";
    cout << sum << endl;
    sum = 0;
    for (auto &el : data)
        sum += el;
    cout << "cpu sum is: \n";
    cout << sum << endl;

    for (int i{0}; i < 10; ++i) {
        cout << res[i] << ", ";
    } cout << endl;
    cout << (float)time[0] << endl;

}


void test_cuda_async() {
    cout << "test async method\n";
    const int len = 1000;

    // 异步操作是通过流来维护的
    // 一个流对应一个顺序提交执行的任务，多个流多个任务，
    // 而且不同流之间还可以并行  
    // 建立并初始化流 
    cudaStream_t stream[2];
    for (int i{0}; i < 2; ++i) {
        cudaStreamCreate(&stream[i]);
    }

    // 异步操作只能通过锁页内存来交换数据，不能直接用malloc或者栈上的内存
    // cpu上分配锁页内存, 有三种方法: 
    float *data, *res;
    vector<float> time(len);
    float sum{0};
    cudaError_t status;
    // 1. 最简单的分配方法
    status = cudaMallocHost(&data, sizeof(float) * len);
    if (status != cudaSuccess) {
        cout << "fail to allocate pinned memory\n";
    }
    // 2. 带选项的分配方法
    status = cudaHostAlloc(&res, sizeof(float) * len, cudaHostAllocDefault);
    if (status != cudaSuccess) {
        cout << "fail to allocate pinned memory\n";
    }
    // 3. 把已有的可分页内存注册成锁负内存
    status = cudaHostRegister(&time[0], sizeof(float) * len, cudaHostRegisterDefault);
    if (status != cudaSuccess) {
        cout << "fail to register as pinned memory\n";
    }
    status = cudaHostRegister(&sum, sizeof(float), cudaHostRegisterDefault);
    std::iota(data, data+len, 0);


    // 像同步一样，也要分配gpu全局内存  
    float *dev_data1{nullptr}, *dev_res{nullptr}, *dev_time{nullptr};
    float *dev_data2{nullptr}, *dev_sum{nullptr};
    cudaMalloc((void**)&dev_data1, sizeof(float) * len);
    cudaMalloc((void**)&dev_res, sizeof(float) * len);
    cudaMalloc((void**)&dev_time, sizeof(float) * len);
    cudaMalloc((void**)&dev_data2, sizeof(float) * len);
    cudaMalloc((void**)&dev_sum, sizeof(float));

    // 定义并行参数
    dim3 block(512);
    dim3 grid(std::min(4096, (int)std::ceil(len / 512.)));

    // 使用流和锁页内存异步调用核函数
    // 为了提高效率最好两个流交替执行，先一起拷数据，再一起运行核函数
    // 1. 使用异步方式把数据拷贝到gpu上去
    status = cudaMemcpyAsync(dev_data1, data, sizeof(float) * len, cudaMemcpyHostToDevice, stream[0]);
    status = cudaMemcpyAsync(dev_data2, data, sizeof(float) * len, cudaMemcpyHostToDevice, stream[1]);
    // 2. 调用核函数，加上stream就是异步的
    compute_square<float><<<grid, block, 0, stream[0]>>>(len, dev_data1, dev_res, dev_time);
    compute_sum<float><<<grid, block, 2048, stream[1]>>>(len, dev_data2, dev_sum);
    // 3. 执行完再拷回来，只是一个请求，异步的，nonblock的
    status = cudaMemcpyAsync(&res[0], dev_res, sizeof(float) * len, cudaMemcpyDeviceToHost, stream[0]);
    status = cudaMemcpyAsync(&sum, dev_sum, sizeof(float), cudaMemcpyDeviceToHost, stream[1]);


    // 等待stream处理完所有的任务 
    // 上面只是向stream提交了请求，运行到这一步的时候不一定已经完成了，所以要在这等上面的stream任务都完成
    for (int i{0}; i < 2; ++i) {
        cudaStreamSynchronize(stream[i]);
    }

    // 检查结果  
    cout << "square: \n";
    for (int i{0}; i < 10; ++i) {
        cout << res[i] << ", ";
    }cout << endl;
    cout << "sum: \n";
    cout << sum << endl;

    // 最后还得回收上面分配的各种资源  
    // 回收上面分配的锁页内存  
    cudaFreeHost(data);
    cudaFreeHost(res);
    cudaHostUnregister(&time[0]);
    cudaHostUnregister(&sum);
    // 回收gpu的内存
    cudaFree(dev_data1);
    cudaFree(dev_res);
    cudaFree(dev_time);
    cudaFree(dev_data2);
    // 销毁上面分配的流
    for (int i{0}; i < 2; ++i) {
        cudaStreamDestroy(stream[i]);
    }
}


int main(void) {
    if (!InitCUDA()) {
        return 0;
    }
    test_cuda_sync();
    test_cuda_async();
    return 0;
}
