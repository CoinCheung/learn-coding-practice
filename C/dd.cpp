#include<iostream>

extern "C"
{
#include"header.h"
#include"malloc.h"
}




using namespace std;

// extern "C"
// {
    
    void printB();
// }

int main(){
    	
    //	for(int i=0;i<13;i++){
            
    //		cout<<"this is "<<i<<endl;
    //	}

    //print();
	int a=3;
	if(a==0)
		cout<<"a==0!"<<endl;
	else if(a==1)
		cout<<"a==1"<<endl;
	else if(a==2)
		cout<<"a==2"<<endl;
	else
		cout<<"a==3"<<endl;

    printf("hello from printf in C in main\n");
    // printA();

    const char *d = "dfdfs";
    const char *dd;
    // const char *d;

    dd = d;
	
    printB();

    int (*aaa)[5];

    aaa = new int[4][5];
    aaa[1][3] = 333;

    cout << aaa[1][3] << endl;
    delete[] aaa;

    // aaa = (int(*)[5])malloc(sizeof(int)*20);
    // free(aaa);


	return 0;
}



void printB()
{

    // for( i = 0; i < 10; i++)
        printf("hello from printB in C\n");
        printA();
}
