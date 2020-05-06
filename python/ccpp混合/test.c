#include<stdio.h>


int var = 100;

void print(){
    printf("hello world from so file");
}

void setVar(int n){
    var = n;
}

int getVar(){
    return var;
}

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
    printf("\n");
    q = NULL;
}




/* main function */
int main(){

    try2DArray();
}
