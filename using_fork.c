#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

// define child function
void childFunction() {
    //print 10 messages and sleep between each message
    for(int i = 0; i < 10; i++){
        printf("Child message: %d\n", i);
        sleep(1);
    }
    _exit(0);
}

// define parent function
void parentFunction() {
    //print 10 messages and sleep between each message
    for(int i = 0; i < 10; i++){
        printf("Parent message: %d\n", i);
        sleep(2);
    }
    _exit(0);
}

int main(int argc, char* argv[]){
    pid_t pid; 

    // use fork() to create a child process
    pid = fork();
    if(pid == -1) {
        fprintf(stderr, "cant fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    if(pid == 0) childFunction();
    else parentFunction();

    // completed successful
    return 0;
}