#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "shm_com.h"

int main(int argc, char const *argv[])
{
    int runing = 1;
    void *shared_memory = NULL;
    struct shared_use_ut *shard_buff;

    int shmid = shmget(1234, sizeof(struct shared_use_ut), 0666 | IPC_CREAT);

    if (shmid == -1)
    {
        printf("shmget failed err=%d\n", errno);
        return 1;
    }

    shared_memory = shmat(shmid, NULL, 0);

    if (shared_memory == (void *)-1)
    {
        printf("shmat failed\n");
        return 1;
    }
    shard_buff = (struct shared_use_ut *)shared_memory;
    shard_buff->written_by_you = 0;

    while (runing)
    {
        if (shard_buff->written_by_you != 0)
        {
            printf("output:%s \n", shard_buff->some_text);
            sleep(2);
            shard_buff->written_by_you = 0;

            if (strncmp(shard_buff->some_text, "end", 3) == 0)
            {
                runing = 0;
            }
        }else
        {
            sleep(2);
        }
    }

    if (shmdt(shared_memory) == -1)
    {
        printf("shmdt failed\n");
        return 1;
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        printf("shmctl failed\n");
        return 1;
    }
    return 0;
}
