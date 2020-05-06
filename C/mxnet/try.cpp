#include<mxnet-cpp/MxNetCpp.h>
#include<string>

// 可以flatten也可以reshape
// conv操作不仅有kernel指定卷积核的大小，还得有weight表示卷积核本身

using mxnet::cpp::Symbol;
using mxnet::cpp::MXDataIter;



/* 
 * definition of the network structure and output
 */
Symbol NetStruct()
{
    using namespace std;
    using namespace mxnet::cpp;

    // input variables
    Symbol x = Symbol::Variable("X");
    auto label = Symbol::Variable("label");

    Symbol conv = Operator("Convolution")
                        .SetParam("kernel", Shape(3,3))
                        .SetParam("num_filter", 64)
                        .SetParam("stride", Shape(1,1))
                        .SetParam("dilate", Shape(1,1))
                        .SetParam("pad", Shape(0,0))
                        .SetParam("no_bias", false)
                        .SetParam("workspace", 512)
                        .SetParam("num_group", 1)
                        .SetInput("data", x)  // 前面的都是设卷积操作的参数，这个是说明卷积的输入数据昌哪个
                        .CreateSymbol("conv"); // 这里根据前面设定好的卷积参数和输入啥的，生成一个Symbol

    return conv;
    
}



/* 
 * training process
 */
void train(MXDataIter train_data , Symbol loss)
{

}



/* 
 * entrance of the program
 */
int main(void)
{
    using namespace std;
    using namespace mxnet::cpp;


    int batch_size = 250;

    // get data
    auto train_iter = MXDataIter("MNISTIter")
        .SetParam("image", "./mnist_data/train-images-idx3-ubyte")
        .SetParam("label", "./mnist_data/train-labels-idx1-ubyte")
        .SetParam("batch_size", batch_size)
        .SetParam("flat", 1)
        .CreateDataIter();

    // get output of network
    auto loss = NetStruct();
    auto s = Shape(4,4);
    cout << endl << s << endl;

    // train the network
    // train(train_iter, loss);


    return 0;
}

