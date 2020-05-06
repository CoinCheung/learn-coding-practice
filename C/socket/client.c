#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include"sys/un.h"
#include<unistd.h>
#include<arpa/inet.h>

#include<stddef.h>
#include<string.h>

#define SERVER "/tmp/unix.domain"



void main()
{
    struct sockaddr_un server_addr;
    int sock_client = -1;
    int res = -1;
    int server_len = 0;

    char *send;
    char buffer[1024];




    /* create a socket */
    sock_client = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock_client == -1)
    {
        perror("fail to create client socket");
        close(sock_client);
        exit(1);
    }



    /* create target server address structure */
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SERVER);
    // server_addr.sun_path[0] = 0;



    /* connect the server */
    server_len = strlen(SERVER) + offsetof(struct sockaddr_un, sun_path);
    server_len = sizeof(server_addr);// - 1;
    res = connect(sock_client, (struct sockaddr *)&server_addr, server_len);
    if(res == -1)
    {
        perror("fail to connect the server");
        close(sock_client);
        unlink(SERVER);
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
        unlink(SERVER);
        exit(1);
    }

    printf("the response from the server is:%s\n",buffer);


    close(sock_client);
    unlink(SERVER);
}
