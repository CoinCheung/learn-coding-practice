#include<iostream>

extern "C"
{
#include"header.h"
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
	
    printB();
	return 0;
}



void printB()
{
    int i = 0;

    // for( i = 0; i < 10; i++)
        printf("hello from printB in C\n");
        printA();
}
