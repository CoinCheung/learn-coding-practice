#include"header.h"

int main(){
    char buffer[1024] = "good morning";
    char * send = "hello";

    // buffer = "hello";
    strcpy(buffer,"hello");

    memset(buffer,'c', sizeof(buffer)-1);
    printf("%s\n",send);



    printf("%s\n",buffer);
    printf("%d\n",strlen(buffer));
    printf("%d\n",sizeof(buffer));

    send = "hello from send";
    strcpy(send, "good");

    printf("%s\n",send);
    printf("%d\n",strlen(send));
    printf("%d\n",sizeof(send));


    // printA();
}
