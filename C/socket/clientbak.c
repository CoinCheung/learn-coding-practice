#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<string.h>



void main()
{
    struct sockaddr_in server_addr;
    int sock_client = -1;
    int res = -1;

    char *send;
    char buffer[1024];




    /* create a socket */
    sock_client = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_client == -1)
    {
        perror("fail to create client socket");
        close(sock_client);
        exit(1);
    }



    /* create target server address structure */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(9736);



    /* connect the server */
    res = connect(sock_client, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(res == -1)
    {
        perror("fail to connect the server");
        close(sock_client);
        exit(1);
    }
                



    /* communicate with server */
    send = "I am client";
    write(sock_client, send, strlen(send));
    // write(sock_client, &ch, 1); // '&ch' is the pointer of the char 'ch'
    memset(buffer, 0, 1024);
    res = -1;
    res = read(sock_client, buffer, sizeof(buffer)); 
    if(res == -1)
    {
        perror("read failed");
        close(sock_client);
        exit(1);
    }
    printf("the response from the server is:%s\n",buffer);

    /* sleep(3); */

    close(sock_client);
}
