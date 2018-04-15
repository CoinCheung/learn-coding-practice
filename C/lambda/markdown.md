

1. fdsdfsdfdsfd
* fdsfdsfdszdf


2. shared_ptr
1) fdsfdsfds
```cpp
    int main(void)
    {
        std::cout << "hello world" << endl;
    }
    #include<memory>

    int main(void)
    {
        int *pi = new int[10];
        std::shared_ptr<int> sp1(p); // 用一个已经存在的普通指针定义

        std::shared_ptr<int> sp2(new int[9]); // 直接用指针初始化

        auto sp3 = std::make_shared<int>(10); // 用make_shared进行定义和初始化

        auto sp4(sp3); // 使用另一个智能指针初始化

        auto sp5(sp3, [](int* data){free(data);}); // 初始化时指定用什么方法析构
    }
```
