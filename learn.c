# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

pthread_mutex_t mutex;

int primes[12] = {1,2,3,5,7,9,11,13,17,19,23,29};  

void *ro(void *arg)
{
    sleep(1);
    int index = (*(int *)arg);
    // if (index % 2)
        printf("hello  %d\n",index);
}


int main(int argc, char const *argv[])
{
    pthread_t t[10];
    pthread_mutex_init(&mutex,NULL);
    int i = 0;

    while (i < 10)
    {
        pthread_create(&t[i],NULL,&ro,&i);
        pthread_join(t[i],NULL);
        i++;
    }
    
    return 0;
}
