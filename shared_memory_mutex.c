#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define NUM_PROC 100

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    int semid, shmid;
    int *shared_sum;


    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }
    union semun arg;
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }


    shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    shared_sum = (int *)shmat(shmid, NULL, 0);
    if (shared_sum == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    *shared_sum = 0;
    struct sembuf P = {0, -1, 0};
    struct sembuf V = {0, +1, 0};

    for (int i = 0; i < NUM_PROC; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {

            int my_num = i + 1;

            if (semop(semid, &P, 1) == -1) {
                perror("semop P");
                _exit(1);
            }

            int tmp = *shared_sum;
            tmp += my_num;
            *shared_sum = tmp;

            if (semop(semid, &V, 1) == -1) {
                perror("semop V");
                _exit(1);
            }

            _exit(0);  
        }
    }

    for (int i = 0; i < NUM_PROC; i++) {
        wait(NULL);
    }

    printf("Sum 1-100: = %d\n", *shared_sum);

    shmdt(shared_sum);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}
