//#include"test.h"
//#include<iostream>
#include<stdio.h>


//using namespace std;


int num = 4;
//string str = "the string in the so file!";
char * str ="the string in the so file by C";


void Print();
int addadd(int a,int b);



void Print(){
    //cout<<add(3,num)<<endl;
    //cout<<str<<endl;

    printf("%d,%c",addadd(3,num),'\n');
    printf("%s,%c",str,'\n');
}

int addadd(int a,int b){
    return a+b;
}


int main(){
    Print();
}
