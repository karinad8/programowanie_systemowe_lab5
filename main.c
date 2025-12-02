#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "server.h"
#include "worker.h"

int main() {
        char str[50];
        int fd[2];
        char str2[50];
        int fd2[2];

        pipe(fd);
        pipe(fd2);

        pid_t pid = fork();

        if (pid == 0) {
                close(fd[1]);
                close(fd2[0]);
                worker_loop(fd[0], fd2[1]);
        }
        else {
                close(fd[0]);
                close(fd2[1]);
                server_loop(fd[1], fd2[0]);
                wait(NULL);
        }
        return 0;
}
