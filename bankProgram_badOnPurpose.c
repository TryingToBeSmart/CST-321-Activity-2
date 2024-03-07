#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_DEPOSITS 1000000 // 1 million

int balance = 0;

// Thread function to deposit money into the bank
void *deposit(void *a)
{
    int x, tmp;
    for(x = 0; x < MAX_DEPOSITS; ++x)
    {
        // Copy the balance to local var, add $1 to the balance,
        // and save the balance to the global var
        tmp = balance;
        tmp = tmp + 1;
        balance = tmp;
    }
    return NULL;
}

// Main: deposit money into bank
int main()
{
    pthread_t tid1, tid2;

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

    // Check balance (will probably be wrong)
    if(balance < 2 * MAX_DEPOSITS)
        printf("\n BAD Balance: bank balance is $%d and should be $%d\n",
            balance, 2 * MAX_DEPOSITS);
    else 
        printf("\n GOOD Balance: Bank balance is $%d\n", balance);

    // Cleanup threads
    pthread_exit(NULL);
    
}