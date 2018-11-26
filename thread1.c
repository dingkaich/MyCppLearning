#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *threadtest(void *par);

int thread_finish = 0;
int main(int argc, char const *argv[])
{
    pthread_t pthread;
    pthread_attr_t pthread_att;
    pthread_attr_init(&pthread_att);
    pthread_attr_setdetachstate(&pthread_att,PTHREAD_CREATE_DETACHED);

    int res = pthread_create(&pthread, &pthread_att, threadtest, NULL);
    if (res != 0)
    {
        printf("pthread_create failed\n");
        return 1;
    }
    pthread_detach(pthread);
    // void *thread_result = NULL;
    // res = pthread_join(pthread, &thread_result);
    // if (res != 0)
    // {
    //     printf("pthread_join failed\n");
    //     return 1;
    // }
    // while (thread_finish != 1)
    // {
    //     printf("wait\n");
    //     sleep(1);
    // }
    printf("this is main\n");
    fflush(NULL);
    pthread_exit(0);
    // printf("game over:%s\n",(char*) thread_result);
}

void *threadtest(void *par)
{
    sleep(2);
    printf("this is thread\n");

    thread_finish = 1;
    pthread_exit("thread game over");
    // return NULL;
}
