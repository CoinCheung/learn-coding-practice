#include"header.h"

    typedef void* (*AddFun)(void*,void*); // 建立一个函数指针

    // 第一个跟函数指针形状相同的函数
    void* add_double(void *para_double1, void *para_double2) 
    {
        double *res = (double*)malloc(sizeof(double));
        *res = *(double*)para_double1 + *(double*)para_double2;

        return (void*)res;
    }

    // 第二个跟函数指针形状相同的函数
    void* add_int(void *para_int1, void *para_int2) 
    {
        int *res = (int*)malloc(sizeof(int));
        *res = *(int*)para_int1 + *(int*)para_int2;

        return (void*)res;
    }

    // 包装函数，使用指针确定哪个函数
    void* add_fun(AddFun f, void* p1, void* p2)
    {
        return f(p1,p2); // 用f 指定是哪个函数，再调用
    }


int main(){
    char buffer[1024] = "good morning";
    /* char * send = "hello"; */

    // buffer = "hello";
    strcpy(buffer,"hello");

    /* memset(buffer,'c', sizeof(buffer)-1); */
    /* printf("%s\n",send); */
    /*  */
    /*  */
    /*  */
    /* printf("%s\n",buffer); */
    /* printf("%ld\n",strlen(buffer)); */
    /* printf("%ld\n",sizeof(buffer)); */
    /*  */
    /* send = "hello from send"; */
    /* strcpy(send, "good"); */
    /*  */
    /* printf("%s\n",send); */
    /* printf("%ld\n",strlen(send)); */
    /* printf("%ld\n",sizeof(send)); */

    int n;
    n = -~0;

    fprintf(stdout, "n is %d\n", n);

    char nn;
    nn = 1;
    while(nn != 0)
        fprintf(stdout, "nn is %d\n", nn++);

    nn = (-1)^(1<<7);
    fprintf(stdout, "largest nn is %hhd\n", nn);

    /* fprintf(stdout, "pi is %lf\n", M_PI); */

    // printA();
    //
        double U1, U2;
        double R, theta, Z;

        srand(time(NULL));
        U1 = (double)rand()/RAND_MAX;

        srand(time(NULL));
        U2 = (double)rand()/RAND_MAX;

        R = sqrt(-2 * log(U2));
        /* theta = 2 * M_PI * U1; */

        Z = R * sin(theta);

        fprintf(stdout, "standard gaussin is %lf\n", Z);

        int a = 1;
        int b = 2;
        int *res;

        res = add_fun(add_int, &a, &b);
        fprintf(stdout, "%d\n", *res);

        free(res);

    int (*aaa)[5];
    a = (int (*)[5])malloc(sizeof(int)*10);

    free(aaa);


}




