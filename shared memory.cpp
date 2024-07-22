#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shmaddr;

    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    shmaddr = (char *)shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    strcpy(shmaddr, "Hello from shared memory!");

    pid_t pid = fork();
    if (pid == 0) {
        printf("Child process: %s\n", shmaddr);
        exit(0);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
        exit(1);
    }

    shmdt(shmaddr);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

