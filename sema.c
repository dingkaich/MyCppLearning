#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#define MAX_SIZE 2048

sem_t *global_sema = NULL;
char message[MAX_SIZE] = {0};

void *testthread(void *a);

int main(int argc, char const *argv[])
{
    // 初始化信号量
    // int res = sem_init(&global_sema, 0, 0);
    // sem_close("test1");
    sem_unlink("test2");
    global_sema = sem_open("test2", O_CREAT | O_EXCL, 0);
    if (global_sema == NULL)
    {
        sem_close(global_sema);
        printf("sem_init failed , res:%d\n", errno);
        exit(1);
    }

    printf("beginning test\n");
    pthread_t p;
    pthread_create(&p, NULL, testthread, NULL);

    printf("please input:\n");

    while (strncmp("end", message, 3) != 0)
    {
        fgets(message, MAX_SIZE, stdin);
        sem_post(global_sema);
    }
    printf("wait thread to stop\n");
    pthread_join(p, NULL);
    printf("thread joined\n");
    sem_close(global_sema);

    return 0;
}

void *testthread(void *a)
{
    int res = sem_wait(global_sema);

    if (res != 0)
    {
        printf("sem_wait failed,res=%d,err=%d\n", res, errno);
        return NULL;
    }

    while (strncmp("end", message, 3) != 0)
    {
        printf("get len=%d\n", (int)strlen(message) - 1);
        sem_wait(global_sema);
    }
    pthread_exit(NULL);
}