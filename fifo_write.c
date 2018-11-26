#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char *fifo_name = "fifo_test";

    if (access(fifo_name, F_OK) != 0)
    {
        int res = mkfifo(fifo_name, 0750);
        if (res != 0)
        {
            printf("mkfifo failed\n");
            return 1;
        }
    }
    char * buffer="good boy";
    int f=open(fifo_name,O_WRONLY|O_NONBLOCK);

    write(f,buffer,8);

    close(f);

    return 0;
}
