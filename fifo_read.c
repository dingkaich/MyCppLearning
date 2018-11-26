#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    char *fifo_name = "fifo_test";

    
    if (access(fifo_name,F_OK) != 0) {
        printf("no file[%s] exist\n",fifo_name);
        return 1;
    }

    // int res = mkfifo(fifo_name, 0750);

    // if (res != 0)
    // {
    //     printf("mkfifo failed\n");
    //     return 1;
    // }
    char buff[1024] = {0};

    int f = open(fifo_name, O_RDONLY);
    int res = 0;
    do
    {
        res = read(f, buff, 1024);

    } while (res > 0);
    close(f);
    printf("data:%s\n", buff);

    return 0;
}
