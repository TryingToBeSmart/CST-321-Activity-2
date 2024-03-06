#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//Thread function
//Takes the thread ID from args and uses it to print messages
void *thread(void *arg)
{
    // Get the thread ID
    pthread_t threadId = pthread_self();

    int x;
    for(x = 0; x < 10; ++x)
    {
        //print a message with the thread ID and counter, then sleep
        printf("Thread %lu....%d\n", (unsigned long)threadId, x);
        sleep(1);
    }
    return NULL;
}

//Entry point to create some threads
int main()
{
    int NUM_THREADS = 3;
    
    // Create variable array of type pthread_t which are used to store thread ids
    pthread_t threadIds[NUM_THREADS];

    // create threads NUM_THREADS times. 
    // The first argument is that address of the variable where
    // the thread ID will be stored.
    // The second argument is the thread attributes, NULL in this case.
    // The third argument is the thread function that will be called.
    // The fourth argument is a pointer to data pased to the thread function
    // In this case we are passing the threadId
    for(int i = 0; i < NUM_THREADS; ++i)
        {
            if(pthread_create(&threadIds[i], NULL, thread, (void *)&threadIds[i]))
            {
                printf("\n ERROR creating thread 1");
                exit(1);
            }
        }

        for(int i = 0; i < NUM_THREADS; ++i)
        {    // Wait for both threads to finish
            if(pthread_join(threadIds[i], NULL))
            {
                printf("\n ERROR joining thread 1");
                exit(1);
            }   
        }

    // Thread creation cleanup
    pthread_exit(NULL);
}