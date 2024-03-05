#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define WAKEUP SIGUSR1
pid_t pid;

// Declare volatile to prevent compiler from optimizing
// away accesses to that variable, ensuring that every 
// access to the variable results in a read or write 
// operation in memory.  This is important because of 
// being handled asynchronously by the signal handler
volatile sig_atomic_t received_signal = 0;

void handle_signal(int sig);

void consumer_process(int iterations) {
    printf("Consumer process starting...\n");

    // Set up signal handler for WAKEUP signal
    signal(WAKEUP, handle_signal);

    // Pause until a signal is received
    pause();

    // Loop for 20 iterations
    for (int i = 0; i < iterations; i++) {
        printf("Consumer: Iteration %d\n", i+1);
        sleep(1); // Sleep for 1 second
    }
    
    printf("Consumer process exiting...\n");
    exit(1); // Exit with return code 1
}

void producer_process(int iterations) {
    printf("Producer process starting...\n");
    
    // Loop for 30 iterations
    for (int i = 0; i < iterations; i++) {
        printf("Producer: Iteration %d\n", i+1);
        sleep(1); // Sleep for 1 second
        if (i + 1 == 5) {
            kill(pid, WAKEUP); // Send WAKEUP signal to the child process
            printf("Producer: Sent WAKEUP signal\n");
        }
    }
    
    printf("Producer process exiting...\n");
    exit(1); // Exit with return code 1
}

void handle_signal(int sig) {
    if (sig == WAKEUP) {
        printf("handle_signal: WAKEUP signal\n");
        received_signal = 1;
    }
}

int main() {
    pid = fork(); // Create child process
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process (consumer)
        consumer_process(20);
    } else {
        // Parent process (producer)
        producer_process(30);
    }
    
    return 0;
}