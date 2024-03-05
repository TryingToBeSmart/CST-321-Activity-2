#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <spawn.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

/*
* Spawn a child processs and wait for it
* to complete
*/
void run_command(char *command){
    pid_t pid;
    char *argv[] = {"sh", "-c", command, NULL};
    int status;

    //Spawn off the provided command run
    printf("Running command... %s\n", command);
    status = posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);
    if(status == 0){
        //All ok
        printf("Child process PID: %i\n", pid);
        if(waitpid(pid, &status, 0) != -1){
            printf("Child process exited with status: %i\n", status);
        }
        else{
            perror("Failed to wait for Child process");
        }
    }
    else{
        //else print error
        printf("Child process failed to spawn with error: %s\n", strerror(status));
    }
}

//Entry to spawn a child process provided argv[1] program argument.
int main (int argc, char* argv[]){
    //Run desired command by spawning off a Child process provided argv[1]
    run_command(argv[1]);
    return 0;
}