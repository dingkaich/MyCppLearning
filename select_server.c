#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int server_sockfd, client_fd;
    int server_len, client_len;

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    int result;
    fd_set readfds, testfds;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9734);
    server_len = sizeof(server_address);

    result = bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    if (result != 0)
    {
        printf("bind error res[%d] ,error[%d]\n", result, errno);
        exit(1);
    }

   result= listen(server_sockfd, 1024);
    if (result != 0)
    {
        printf("listen error res[%d] , error[%d]\n",result,errno);
        exit(1);
    }

    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds);

    for (;;)
    {
        char ch[128] = {0};
        int fd;
        int nread;

        testfds = readfds;
        printf("server waiting\n");

        result = select(FD_SETSIZE, &testfds, NULL, NULL, NULL);

        printf("we get %d connect\n",result);

        for (fd = 0; fd < FD_SETSIZE; fd++)
        {

            if (FD_ISSET(fd, &testfds))
            {

                //new connect
                if (fd == server_sockfd)
                {
                    client_len = sizeof(client_address);
                    client_fd = accept(fd, (struct sockaddr *)&client_address, &client_len);
                    FD_SET(client_fd, &readfds);
                    printf("adding client on fd %d \n", client_fd);
                }
                else
                {
                    ioctl(fd, FIONREAD, &nread);
                    if (nread == 0)
                    {
                        close(fd);
                        FD_CLR(fd, &readfds);
                        printf("removing client on fd:%d\n", fd);
                    }
                    else
                    {
                        read(fd, ch, 128);
                        usleep(200);
                        printf("serving clienton fd:%d \n", fd);
                        write(fd, "receive okay\n", 13);
                    }
                }
            }
        }
    }

    return 0;
}
