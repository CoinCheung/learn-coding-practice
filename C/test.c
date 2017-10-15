#include"header.h"

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

    // printA();
}
