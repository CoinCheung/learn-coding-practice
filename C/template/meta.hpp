#ifndef _META_HPP_
#define _META_HPP_

template<int N>
long fun()
{
    return fun<N-1>() + fun<N-2>();
}

template<>
long fun<1>()
{
    return 1;
}

template<>
long fun<0>()
{
    return 0;
}

//
// #include<iostream>
// int main(void)
// {
//     std::cout << "f is: " << fun<50>() << std::endl;
//
//     return 0;
// }

template<int N>
struct fib
{
    enum {Result = fib<N-1>::Result + fib<N-2>::Result};
};

template<>
struct fib<0>
{
    enum {Result=0};
};

template<>
struct fib<1>
{
    enum{Result=1};
};


#endif
