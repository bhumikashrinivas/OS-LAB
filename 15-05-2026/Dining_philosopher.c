 #include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define N 5
sem_t forks[N];
pthread_t philosophers[N];
void* philosopher(void* num)
{
    int id = *(int*)num;
    for(int i = 0; i < 2; i++)
    {
        printf("Philosopher %d is Thinking\n", id);
        sleep(1);
        if(id == N-1)
        {
            sem_wait(&forks[(id+1)%N]);
            sem_wait(&forks[id]);
        }
        else
        {
            sem_wait(&forks[id]);
            sem_wait(&forks[(id+1)%N]);
        }
        printf("Philosopher %d is Eating\n", id);
        sleep(2);
        sem_post(&forks[id]);
        sem_post(&forks[(id+1)%N]);
        printf("Philosopher %d finished Eating\n", id);
    }
}
int main()
{
    int ids[N];
    for(int i=0;i<N;i++)
        sem_init(&forks[i],0,1);
    for(int i=0;i<N;i++)
    {
        ids[i]=i;
        pthread_create(&philosophers[i],NULL,philosopher,&ids[i]);
    }
    for(int i=0;i<N;i++)
        pthread_join(philosophers[i],NULL);
    return 0;
}
