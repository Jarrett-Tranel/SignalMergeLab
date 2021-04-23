#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int randNums [10];
int childrenPIDS[1000];

void childHandler (int signum)
{
    printf("I am PID %d \n", getpid());
    if (randNums[1] == 0) //we are dealing with a one list(fully sorted)
    {
        printf("There's just one element here hehe haha\n");
    } 
    else //We need to split the work among more children
    {
        printf("There is more then one element!\n");
    }
}

int main()
{
    if (randNums[0] == NULL)
    {
        time_t t;
        srand((unsigned) time(&t));
        printf("I am PID: %d \n", getpid());
        for(int i = 0; i<= 10; i++)
        {
            randNums[i] = (rand() % 300);
            printf("At bucket %d we have the random value %d \n", i, randNums[i]);
        }
        printf("%d \n", getpid());
    }

    while (randNums[1] != NULL)
    {
        pid_t pid1 = fork();
        pid_t pid2 = fork();
    
        if(pid1 < 0)
        {
            printf("Fork 1 Failed\n");
            exit(1);
        }

        if(pid2 < 0)
        {
            printf("Fork 2 Failed\n");
            exit(1);
        }
        int arraySize = sizeof(randNums)/sizeof(int);
        printf("Array size = %d \n", arraySize);
        if(pid1 == 0) //first child
        {
            arraySize = arraySize/2;
            
            for (int i = arraySize; i<= (sizeof(randNums)/sizeof(int)); i++)
            {
                randNums[i] = NULL;
            }
            printf("I am PID %d \n", getpid());
            printf("My list is ");
            for (int j = 0; j < arraySize; j++)
            {
                
                printf("%d ", randNums[j]);
                
            }
            printf("\n");
        }
        if (pid2 == 0) //second child
        {
            arraySize = arraySize/2;
            
            for (int i = arraySize; i<= (sizeof(randNums)/sizeof(int)); i++)
            {
                randNums[i-arraySize] = randNums[i];
                randNums[i] = NULL;
            }
            printf("I am PID %d \n", getpid());
            printf("My list is ");
            for (int j = 0; j < arraySize; j++)
            {
                
                printf("%d ", randNums[j]);
                
            }
            printf("\n");
        }

        pause(); 
    }
   
}