#include<stdlib.h>   //to use rand()
#include<unistd.h>  //to use usleep()
#include<stdio.h> 
#include<pthread.h>    //to use semaphores
#include<semaphore.h>
#include<malloc.h>
#include<signal.h>
#include<sys/types.h>

sem_t philo;
sem_t chops[100];  //semaphore array for chopsticks
int *phils;        //array for philosophers
int n;   //no.of Philosophers
int *cycle;   //array to count Eat/think cycle for each philosopher
int termcount=0;    //count for SIGTERM

void eat(int);
void think(int);
void intialize_semaphores(void);

void handler(int sig)
{
  int i;
  if(sig==SIGTERM)
    {
	termcount++;
	for(i=0;i<n;i++)
	  {
	     fprintf(stderr,"\nPhilosopher  %d completed %d cycles",i,cycle[i]);
	     sem_close(&chops[i]);
	     sem_destroy(&chops[i]);
	  }
    }
  exit(sig);
}

void initialize_semaphores()
{
  int i;
  for(i=0;i<n;i++)  //Initializing philosophers array and cycle array
      {
        phils[i]=i;
        cycle[i]=0;
      }

  for(i=0;i<n;i++)   //initialzing semaphores for N chopsticks
   if(sem_init(&chops[i],0,1)<0)
    {
    printf("\nERROR while initialzing semaphores");
    exit(EXIT_FAILURE);
    }
   
  if(sem_init(&philo,0,n-1)<0) //semaphore of value N-1 which allows only N-1 to eat at a time
    {
    printf("\nError while initializing semaphores");
    exit(EXIT_FAILURE);
    }

}


void* philosopher(void *num)
{
/* semaphore philo allows only N-1 philosophers to pickup the chopsticks at a time and eat which prevents the deadlock as there will be always one extra chopstick left on table*/
while(termcount==0)  //check if SIGTERM received or not, if received exit while 
    {

	int *i=num;	
	sem_wait(&philo);
        sem_wait(&chops[*i]);  //pick left chopstick
        sem_wait(&chops[(*(i+1))%(n)]);  //pick right chopstick
	  
        eat(*i);   
        usleep(rand()%1000000);

	sem_post(&chops[*i]);//put back left chopstick
	sem_post(&chops[(*(i+1))%(n)]);//put back right chopstick

	think(*i);
        usleep(rand()%1000000);
        sem_post(&philo);
        cycle[*i]++;
    }
}
void eat(int i)
    {
	printf("\nPhilospher %d is eating",i);
    }
void think(int i) 
    {
	printf("\nPhilosopher %d is thinking",i);
    }


int main(int argc,char *argv[])
{
  if(argc<1)
    {
	printf("ERROR,not enough arguments");
	exit(EXIT_FAILURE);
    }
 int seats,i;
 seats=argv[1][0]-'0';

 n=seats;  //No. of philosophers(assigning to global variable n);
 pthread_t thread_id[n];
 phils=(int*)malloc(n*sizeof(int)); //assiging space for array of 'n' no. of philosphers 
 cycle=(int*)malloc(n*sizeof(int));//allocating space for cycle array which calculates number of cycles of eating and thinking of each philosopher

 initialize_semaphores();

 signal(SIGTERM,handler);  //catching any SIGTERM signal

 fprintf(stderr,"\nProcess ID = %d",getpid());  //printing PID 

//creating phiosopher threads and printing PID for each thread
 for(i=0;i<n;i++)
     {
	pthread_create(&thread_id[i],NULL,philosopher,&phils[i]);
	printf("\nPID of phil[%d]=%d",i,getpid());
     }


 for(i=0;i<n;i++)   //joining threads after termination
   pthread_join(thread_id[i],NULL);

exit(EXIT_SUCCESS); 
}
