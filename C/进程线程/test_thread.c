#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

typedef struct
{
    int a;
    char b;
}thread_parameter;

pthread_t thread; 

// subthread
void *thread_run(void *args)
{
    thread_parameter *tp = NULL;

    // pthread_detach(pthread_self());

    tp = (thread_parameter *)args;
    fprintf(stdout,"parameters got from main thread are: %d, %c\n",tp->a, tp->b);
    fputs("thread with para created~\n", stdout);
}

// main thread and main process, do not let the process end too early
int main()
{
    int thread_result;
    thread_parameter tp;

    fputs("in main thread\n",stdout);

    tp.a = 10;
    tp.b = 'c';

    fputs("creating thread ...",stdout);
    thread_result = pthread_create(&thread, NULL, thread_run, &tp);
    if(thread_result != 0)
    {
        perror("create thread failed: ");
        exit(0);
    }
//    pthread_exit(NULL);
    fputs("succeed\n",stdout);
    pthread_join(thread,NULL);
}
