#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(){
    pid_t pid;
    
    pid = fork();
    printf("First fork() PIDs: %d\n", getpid());

    pid = fork();
    printf("Second fork() PIDs: %d\n", getpid());

    exit(0);
}