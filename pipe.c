#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void readpipe()
{
    FILE *f;
    char buffer[1023 + 1] = {0};
    f = popen("uname -a", "r");

    if (f != NULL)
    {

        if (fread(buffer, sizeof(char), 1023, f) > 0)
        {

            printf("output:%s\n", buffer);
            pclose(f);
        }
    }
    return;
}

void writepipe()
{
    FILE *f;
    char buffer[1023 + 1] = {0};

    sprintf(buffer,"asdfadsfsdafsadf");
    f = popen("od -c", "w");

    if (f != NULL)
    {

        if (fwrite(buffer, sizeof(char), strlen(buffer), f) > 0)
        {
            // printf("output:%s\n", buffer);
            pclose(f);
        }
    }
    return;
}

void testpipe()
{
    int len;
    int file_pipe[2]={0};
    const char * msg="123";
    char buf[BUFSIZ+1]={0};
    int res = pipe(file_pipe);
    
    if (res!=0) {
        printf("init pipe failed\n");
        return;
    }
    
    len= write(file_pipe[1],msg,strlen(msg));
    printf("write len = %d\n",len);
    len = read(file_pipe[0],buf,BUFSIZ);
    printf("read len = %d\n",len);
    printf("read msg = %s\n",buf);

    return ;
}


int main(int argc, char const *argv[])
{
    readpipe();
    writepipe();
    testpipe();
    return 0;
}
