#include<stdio.h>
#include"sys/types.h"
#include"sys/socket.h"
#include"sys/un.h"
#include<unistd.h> //包括linux下的read() write()等函数

#include<stdlib.h>

#define SERVER "/tmp/unix.domain"

void main()
{
    /* definitions  */
    int sock_server = -1;
    int sock_client = -1;
    int ret = -1;
    int clientnum;
    int len;

    struct sockaddr_un server_addr; // server address struct
    struct sockaddr_un client_addr; // client address struct

    char recv_buffer[1024];
    char *res = "message received";



    /* create server address structure */
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SERVER);
    // server_addr.sun_path[0] = 0;



    /* create server socket */
    sock_server = socket(AF_UNIX, SOCK_STREAM, 0); // internet mode, tcp
    if(sock_server == -1)
    {
        perror("create socket server failed");
        close(sock_server);
        exit(1);
    }



    /* bind the socket with address structure */
    ret = -1;
    ret = bind(sock_server,(struct sockaddr *)&server_addr,sizeof(server_addr)); // - 1);
    if(ret == -1)
    {
        perror("cannot bind server socket and address structure");
        close(sock_server);
        unlink(SERVER);
        exit(1);
    }



    /* listen to the port through socket */
    ret = -1;
    ret = listen(sock_server,1); // length of the queue is 1, no more than 1 client are allowed to queue
    if(ret == -1)
    {
        perror("cannot listen to the server socket");
        close(sock_server);
        unlink(SERVER);
        exit(1);
    }



    /* establish the connection and accept the client */
    len = sizeof(client_addr);
    sock_client = accept(sock_server, (struct sockaddr *)&client_addr, &len);
    if(sock_client == -1)
    {
        perror("cannot accept client connection");
        close(sock_server);
        unlink(SERVER);
        exit(1);
    }



    /* recieve the request and response */
    memset(recv_buffer,0,1024);
    clientnum = read(sock_client, recv_buffer, sizeof(recv_buffer));
    printf(" client number is: %d\n", clientnum);
    printf(" client message is: %s\n", recv_buffer);

    
    write(sock_client, res, strlen(res));

    

    /* close the socket */
    close(sock_client);
    close(sock_server);
    unlink(SERVER);

}
