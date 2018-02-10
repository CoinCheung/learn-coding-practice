#include<memory>
#include<iostream>


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

    return 0;
}

