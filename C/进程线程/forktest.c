#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void main()
{
    pid_t pid;
    
    printf("当前进程是%d\n",getpid());
    
    pid = fork();
    if(pid < 0)
    {
       perror("fail to create sub-process");
       exit(0);
    }
    else if(pid == 0)
    {
       printf(" 这是子进程pid = %d 父进程的pid = %d\n",getpid(),getppid());
    }
    else
       printf("这是父进程 pid = %d 父进程的pid = %d\n",getpid(),getppid());
}
