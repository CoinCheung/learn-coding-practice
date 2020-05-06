
#include<iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include<cuda_runtime.h>


using std::cout;
using std::endl;
using std::vector;



template<typename scalar_t>
__global__ void compute_squ_sum(const int num, const scalar_t* data, scalar_t* res, scalar_t* sum, clock_t* time) {
/* __global__ void compute_squ_sum(const int num, scalar_t* res) { */
    const int tid = threadIdx.x;
    const int bid = blockIdx.x;
    const int th_idx = bid * blockDim.x + tid;
    int stride = blockDim.x * gridDim.x;
    for (int i{th_idx}; i < num; i+=stride) {
        res[i] = data[i] * data[i];
        res[i] = 10;
    }
    res[0]=111;
    res[1]=111;
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
    vector<int> inp(len);
    /* vector<int> res(len); */ // this should not do
    int res[len];
    std::iota(inp.begin(), inp.end(), 0);

    for (int i{0};i<1000; ++i) res[i] = i;

    // allocate memory
    int *data{nullptr}, *squ{nullptr};
    int sum{0};
    clock_t *time;
    cudaMalloc((void**)&data, sizeof(int) * len);
    cudaMalloc((void**)&squ, sizeof(int) * len);
    cudaMalloc((void**)&time, sizeof(clock_t) * len);

    // copy data to device
    cudaMemcpy(data, inp.data(), sizeof(int) * len, cudaMemcpyHostToDevice);

    // execute kernel function
    dim3 block(512);
    dim3 grid(std::ceil(len / 512.));
    compute_squ_sum<int><<<32, 512, 0>>>(len, data, squ, &sum, time);
    /* compute_squ_sum<int><<<32, 512, 0>>>(len, squ); */

    // copy results back to host
    cudaMemcpy(&res, squ, sizeof(int) * len, cudaMemcpyDeviceToHost);

    // free allocated memory
    cudaFree(data);
    cudaFree(squ);
    cudaFree(time);

    cout << sum << endl;
    for (int i{0}; i < 10; ++i) {
        cout << res[i] << ", ";
    } cout << endl;
}

int main(void) {
    if (!InitCUDA()) {
        return 0;
    }
    // kernel<<<2, 2>>>();
    // check_gpu_info();
    test_cuda_sync();
    return 0;
}
