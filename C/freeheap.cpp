#include<malloc.h>
#include<stdio.h>
#include<string>
#include<iostream>
#include<string.h>

using std::string;
using std::cout;
// using std::<<;

void freeheap(void *hp);

class exp
{
    public:
        int a = 9;
        double * b;
        const char * s = "good morning\n" ;
        string str;

        void fun();
};

void exp::fun()
{
    fprintf(stdout, "a value is: %d\n", a);
    fprintf(stdout, "s value is: %s\n", s);
    cout<<str;
    cout<<a;
}




int main()
{
    double *hp = (double *)malloc(sizeof(double)*10);
    exp *xp = NULL;

    xp = (exp *)malloc(sizeof(exp));
    const char *cp = "didid";
    char *tcp = NULL;

    tcp = (char *)malloc(10);

    memset(tcp, 0, 10);
    memcpy(tcp,cp, 4);
    fprintf(stdout,"string is %s\n",tcp);

    fprintf(stdout,"cp before changed is %s\n",cp);
    cp = "dddfffddddddddddddddddddddddddffffff";
    fprintf(stdout,"cp after changed is %s\n",cp);

    // memcpy("ccccc",cp, 4);
    // fprintf(stdout,"string is %s\n",cp);

    freeheap(tcp);

    xp->s = "ddddggg";
    xp->s = "ccddggg";
    fprintf(stdout,"string is %s\n",cp);
    fprintf(stdout,"s in obj is %s\n",xp->s);
    // xp->a = 5;
    xp->str = "hello\n";
    xp->fun();

    freeheap(hp);
    freeheap(xp);

    return 0;
}

void freeheap(void *hp)
{
    free(hp);
}


