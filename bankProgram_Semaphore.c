#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>

#define MAX_DEPOSITS 1000000 // 1 million
int balance = 0;
int depositAmount = 1;
sem_t* semaphore;


// Thread function to deposit money into the bank
void *deposit(void *a)
{
    int x, tmp;
    for(x = 0; x < MAX_DEPOSITS; ++x)
    {
        // *** Start of Critical Region ***
        // lock it down for 1 thread at a time
        sem_wait(semaphore);

        // Copy the balance to local var, add $1 to the balance,
        // and save the balance to the global var
        tmp = balance;
        tmp = tmp + 1;
        balance = tmp;

        // *** End of Critical region ***
        // Unlock
        sem_post(semaphore);
    }
    return NULL;
}

// Main: deposit money into bank
int main()
{
    pthread_t tid1, tid2;

    // Create a semaphore to be used in the critical region
    semaphore = sem_open("Semaphore", O_CREAT, 00644, 1);
    if(semaphore == SEM_FAILED)
    {
        printf("\n ERROR creating semaphore");
        exit(1);
    }

    // Create 2 threads (users) to deposit funds into bank
    // created with address of tid(1 or 2), NULL attributes, 
    // pass the deposit function, NULL data to pass
    if(pthread_create(&tid1, NULL, deposit, NULL))
    {
        // if error
        printf("\n ERROR creating deposit thread 1");
        exit(1);
    }
    if(pthread_create(&tid2, NULL, deposit, NULL))
    {
        // if error
        printf("\n ERROR creating deposit thread 2");
        exit(1);
    }

    // Wait for threads (users) to finish depositing funds to bank
    if(pthread_join(tid1, NULL))
    {
        printf("\n ERROR joining deposit thread 1");
        exit(1);
    }
    if(pthread_join(tid2, NULL))
    {
        printf("\n ERROR joining deposit thread 2");
        exit(1);
    }

    // Check balance
    if(balance < 2 * MAX_DEPOSITS)
        printf("\n BAD Balance: bank balance is $%d and should be $%d\n",
            balance, 2 * MAX_DEPOSITS);
    else 
        printf("\n GOOD Balance: Bank balance is $%d\n", balance);

    // Cleanup threads and semaphore
    sem_close(semaphore);
    pthread_exit(NULL);
    
}