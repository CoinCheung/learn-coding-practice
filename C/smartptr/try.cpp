#include<memory>
#include<iostream>
#include<cassert>


using std::shared_ptr;
using std::cout;
using std::endl; 


shared_ptr<int> fun(shared_ptr<int> sp)
{
    shared_ptr<int> sp_local(new int[10], [](int* data){free(data); cout << "data freed" << endl;});
    int *p = new int[10];

    p[9] = 9;
    for(int i = 0; i < 10; i++)
        sp_local.get()[i] = i;

    cout << sp_local.use_count() << endl;

    return sp_local;
}


void try_sp();

int main(void)
{
    shared_ptr<int> sp(new int[100]);
    shared_ptr<int> sp2;
    int *pi = new int[10];
    shared_ptr<int> sp3(pi);
    
    cout << sp.use_count() << endl;
    sp2 = sp;
    sp3 = sp;
    cout << sp.use_count() << endl;
    // sp = NULL;
    sp.reset(new int[9]);
    cout << sp.use_count() << endl;
    cout << sp2.use_count() << endl;
    // sp = sp3;
    cout << sp.use_count() << endl;
    cout << sp.unique() << endl;

    cout << sp.use_count() << endl;
    sp2.reset();
    sp2 = sp;
    sp3 = sp;
    cout << sp.use_count() << endl;
    // sp.get() = new int[3];

    int *pi2 = NULL;

    pi2 = sp.get();
    pi2[1] = 444;
    cout << sp.get()[1] << endl;
    // cout << (*sp)[1] << endl;
    // cout << sp(1) << endl;
    //

    auto sp4(sp);
    cout << sp.use_count() << endl;

    fun(sp);
    cout << sp.use_count() << endl;
    std::weak_ptr<int> wp;
    wp = sp;
    cout << sp.use_count() << endl;
    cout << wp.use_count() << endl;
    // sp = NULL;
    sp.reset();
    cout << sp.use_count() << endl;

    double m;
    for(auto i = 0; i < 10; i++)
    {
        cout << typeid(m).name() << endl;
    }

    // sp = nullptr;
    // int *arr = new int[10];
    int arr[10] = {9};
    for(auto i = 0; i < 10; i++)
        arr[i] = i;
    cout << std::begin(arr) << endl;
    cout << std::end(arr)[-1] << endl;

    shared_ptr<int> sp5(sp);

    sp5 = fun(sp);
    cout << sp5.use_count() << endl;

    try_sp();

    return 0;
}


void try_sp()
{
    using namespace std;

    shared_ptr<int> sp(new int{3});

    cout << "try_sp" << endl;
    cout << *sp << endl;

    shared_ptr<int> sp2 = make_shared<int>(10);
    cout << sp2.get()[0] << endl;
    
    shared_ptr<int> sp3(new int[10]{1,1,1,1,1}, [](int *p){delete[] p;});
    cout << sp3.get()[3] << endl;
    cout << *(sp3.get()+3) << endl;


    cout << "20180228" << endl;
    weak_ptr<int> wp1{sp3};
    weak_ptr<int> wp2 = sp3;
    weak_ptr<int> wp3(sp3);

    auto spp = wp1.lock();
    assert(spp!=nullptr);
    cout << *spp.get() << endl;

    cout << "20180310" << endl;
    shared_ptr<int[4][4]> sp(new int[4][4]);
    auto sp_ptr = sp.get();
    // for(auto i{0}; i<4; i++)
    //     for(auto j{0}; j<4; j++)
    //         sp_ptr[i][j] = i*j;

}

