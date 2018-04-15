#include<iostream>
#include<cmath>
#include<memory>
#include<time.h>
#include<cassert>


typedef unsigned int uint32;
typedef unsigned long uint64;

void get_rand(std::shared_ptr<int> sp, uint32 len, uint64 seed);
void heapsort(std::shared_ptr<int> sp, uint32 len);
void build_heap(std::shared_ptr<int> sp, uint32 len);
void print(std::shared_ptr<int> sp, uint32 len);
uint32 get_heapsize(uint32 len);;
void sink(std::shared_ptr<int> sp, int node, uint32 len);
void check_sorted(std::shared_ptr<int> sp, int len);



int main()
{
    uint len{21};
    std::shared_ptr<int> sp(new int[len], [](int *p){delete[] p;});

    for (int i{0}; i<100000; i++)
    {
        get_rand(sp, len, time(0));
        // std::cout << "randomly generated numbers: " << std::endl;
        // print(sp, len);

        heapsort(sp ,len);
        // std::cout << std::endl << "sorted numbers: " << std::endl;
        // print(sp, len);
        check_sorted(sp, len);
    }

    return 0;
}



void get_rand(std::shared_ptr<int> sp, uint32 len, uint64 seed)
{
    srand(seed);
    int *p{sp.get()};

    for (uint32 i{0}; i<len; i++)
        p[i] = rand() % 100;
}




void print(std::shared_ptr<int> sp, uint32 len)
{
    using namespace std;
    int *p{sp.get()};

    for (uint32 i{0}; i<len; i++)
        cout << p[i] << ", ";
    cout << endl;
}



void heapsort(std::shared_ptr<int> sp, unsigned int length)
{
    int *p{sp.get()};
    long len{static_cast<long>(length)};

    assert(len > 0);

    // 调整成大根堆
    build_heap(sp, len);
    // 把根结点与最后的结点交换，然后len--，再把换上来的结点下沉以重新得到大根堆
    for (int i{1}; i<len; i++)
    {
        // swap p[0] and the rear element
        p[0] = p[0] ^ p[len-i];
        p[len-i] = p[0] ^ p[len-i];
        p[0] = p[0] ^ p[len-i];

        sink(sp, 0, len-i);
    }
}



void build_heap(std::shared_ptr<int> sp, uint32 len)
{
    long parent;

    // 从最后一个非叶子结点向前一个一个的下沉就能得到大根堆
    // 最后一个非叶子结点的索引是len/2-1
    for (parent=((len>>1)-1); parent >=0 ; parent--)
    {
        sink(sp, parent, len);
    }
}


void sink(std::shared_ptr<int> sp, int node, uint32 length)
{
    int *p{sp.get()};
    int Maxind;
    int parent;
    int child1;
    int child2;
    int len{static_cast<int>(length)};

    // 给定一个结点，找到这个结点的比较大的子结点，如果子结点比
    // 父结点大就交换，交换后再调整交换的子结点
    parent = node;
    while(true)
    {
        child1 = (parent<<1) + 1;
        child2 = (parent<<1) + 2;

        if (child1 >= len)
            return;

        if (child2 >= len)
            Maxind = child1;
        else
            Maxind = p[child1]>p[child2]?child1:child2;

        if (p[Maxind] > p[parent])
        {
            p[Maxind] = p[Maxind] ^ p[parent];
            p[parent] = p[Maxind] ^ p[parent];
            p[Maxind] = p[Maxind] ^ p[parent];
        }

        // 下沉操作是递归进行的，因为只交换之后可能会破坏子树
        // 结构，使子树不再是大根堆，所以要递归调整
        parent = Maxind;
    }

}


uint32 get_heapsize(std::shared_ptr<int> sp, uint32 len)
{
    int ind{0};
    uint32 heap_size;

    while (true)
    {
        heap_size = pow(2, ind++) - 1;
        if (heap_size >= len)
            break;
    }

    return heap_size;
}



void check_sorted(std::shared_ptr<int> sp, int len)
{
    int *p{sp.get()};

    for(int i{1}; i<len; i++)
        if(p[i] < p[i-1])
        {
            std::cout << "sort failed !!" << std::endl;
            break;
        }
    std::cout << "sort succed !!" << std::endl;
}
