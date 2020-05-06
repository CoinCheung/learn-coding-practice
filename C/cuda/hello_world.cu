#include<iostream>
#include<cuda_runtime.h>

using std::cout;
using std::endl;


__global__ void kernel(void) {

}

void check_gpu_info() {
    int dev = 0;
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

int main(void) {
    kernel<<<2, 2>>>();
    printf("hello world\n");
    check_gpu_info();
    return 0;
}
