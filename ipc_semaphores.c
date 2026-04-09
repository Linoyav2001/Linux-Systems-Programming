#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUMOFSEM 5

void increment_others(int i);
void cleanup_semaphores();
int semid;
struct sembuf sops[1];
union semun
{
    int val;
    struct semid_ds *buff;
    unsigned short *array;
    struct seminfo *_buf;

};
union semun semarg;

int main()
{
    int i, j, k, status;
    pid_t pid[5];

    semid = semget(IPC_PRIVATE, 5, 0600);

    for (i = 1; i < 17; i++)
    {
        signal(i, &cleanup_semaphores);
    }

    // Semaphores
    for (i = 0; i < NUMOFSEM; i++)
    {
        semarg.val = 4 - i;
        semctl(semid, i, SETVAL, semarg);
    }

    sops->sem_num = 0;
    sops->sem_flg = 0;

    printf("\nOutput:Print 1-100 with 5 Semaphores\n");
    for (i = 0; i < 5; i++)
    {
        if (fork() == 0)
        {
            struct sembuf sop = {
                i,
                -4,
            };
            for (j = i + 1; j < 101; j += 5)
            {
                semop(semid, &sop, 1);
                printf("Semaphore %d : %d \n", (i + 1), j);
                increment_others(i);
            }
            exit(0); // Child Finished
        }
    }
    do ;
     while (wait(&status) > 0); // Wait until all the children finish
    printf("\n");
    cleanup_semaphores();
    return 0;
}


void increment_others(int i)
{
    int k;
    for (k = 0; k < 5; k++)
    {
        if (k != i)
        {
            sops->sem_op = 1;
            sops->sem_num = k;
            semop(semid, sops, 1);
        }
    }

}

void cleanup_semaphores()
{
    semctl(semid, 0, IPC_RMID, semarg);
    exit(1);
}



