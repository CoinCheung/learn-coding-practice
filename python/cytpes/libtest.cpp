#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;

int var = 100;

extern "C"
void print(){
    for(int i = 0; i < 1000; i++)
        printf("hello world from so file\n");
}

extern "C"
void setVar(int n){
    var = n;
}

extern "C"
int getVar(){
    return var;
}

extern "C"
void calMix(void *in,int row, int colomn,void *out){
    double *pout = (double*)out;
    pout[2*row+2] = 5;
}

void try2DArray(){
    int a[4][4];
    int *p = NULL;

    a[2][2] = 3;
    a[2][3] = 4;
    p = (int*)a;
    printf("\na[2][2] is: %d",p[2*4+2]);
    p = NULL;

    int *q = NULL;
    q = a[2];
    printf("\na[2][3] is: %d",*(q-2*4+3));
    printf("\na[2][3] is: %d",q[-2*4+3]);
    q = NULL;
}


/* a cpp class generated below */
extern "C"
class myClass{
    public:
        int a = 1;
        string str = "hello from the class";

        void printA();
        void printStr();

};

extern "C"
void myClass::printA(){
    cout << a <<endl;
}

extern "C"
void myClass::printStr(){
    for(int i = 0; i < 1000;i ++)
        cout << str << endl;
}

myClass dd;

extern "C"
void printMyClassStr(myClass mc){
    mc.printStr();
}

/* main function */
int main(){
    myClass cc;
    cout << cc.a;
    cc.printStr();

    try2DArray();
}
