#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>


void ding(int sig)
{
    printf("ding\n");
    return ;
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    pid_t currentpid;
    pid_t ppid;
    char *message;
    int n;
    printf("this is fork starting\n");

    // fflush(NULL); //-->有没有这个函数很重要，没有的话，上面的会打印2遍，有的话只会打印一遍，可以看出进程的复制包含了进程的一切信息

    pid = fork();

    switch (pid)
    {
    case -1 /* constant-expression */:
        /* code */
        printf("fork error");
    case 0:
        currentpid = getpid();
        ppid = getppid();
        printf("this is child process,currentpid:%d,ppid:%d\n", currentpid, ppid);

        exit(-1);
    default:
        currentpid = getpid();
        ppid = getppid();

        printf("this is father process,currentpid:%d,ppid:%d\n", currentpid, ppid);
        int status;
        waitpid(-1, &status, 0);
        printf("status:%d", status);
    }

    fflush(NULL);
    alarm(2);
    signal(SIGALRM,ding);
    pause();
    printf("alarm\n");
    fflush(NULL);
    sleep(5);
    return 0;
}
