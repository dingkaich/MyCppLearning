#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *threadtest(void *par);

int main(int argc, char const *argv[])
{
    pthread_t pthread;
    int res = pthread_create(&pthread, NULL, threadtest, NULL);
    if (res != 0)
    {
        printf("pthread_create failed\n");
        return 1;
    }
    void *thread_result = NULL;
    res = pthread_join(pthread, &thread_result);
    if (res != 0)
    {
        printf("pthread_join failed\n");
        return 1;
    }

    printf("game over:%s\n",(char*) thread_result);
}

void *threadtest(void *par)
{
    printf("this is thread\n");
    sleep(2);
    pthread_exit("thread game over");
    // return NULL;
}
