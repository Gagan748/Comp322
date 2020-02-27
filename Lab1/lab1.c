#include<stdio.h>
#include<stdlib.h>       //to define exit()
#include<time.h>           //needed for time() system call
#include<sys/times.h>       //needed for times() system call to print user/system time
#include<stdint.h>   //used for casting clock_t to uintmax_t for printf
int main()
{
time_t start;
time_t stop;
pid_t cpid;                // to store ID of child
int status;                // to store status of child process 

time(&start);
printf("\nSTART:%ld\n",start);

cpid=fork();
struct tms t;


if(cpid==0)    //if child is executing
{
printf("\nPPID:%d, PID:%d",getppid(),getpid());
exit(EXIT_SUCCESS);
}
else if(cpid>0)    //parent is executing
{
//parent process waiting for child to exit using waitpid
waitpid(cpid,&status,0);
//child process exited
int i;
times(&t); //system call to print user time and system time
for( i=0;i<1000000;i++)             //loop to keep on system running for sometime
time(NULL);

//printing pid, ppid , retval and status of child process 
printf("\nPPID:%d, PID:%d, CPID:%d, RETVAL:%d",getppid(),getpid(),cpid,status);

//printing user time and system time of parent and child process
printf("\nUSER:%ju, SYSTEM:%ju",(uintmax_t)t.tms_utime,(uintmax_t) t.tms_stime);
printf("\nCUSER:%ju, CSYSTEM:%ju\n",(uintmax_t)t.tms_cutime,(uintmax_t)t.tms_cstime); 
}

else
{
printf("\nchild not created, ERROR");
exit(EXIT_FAILURE);
}
time(&stop);
printf("\nSTOP:%ld\n",stop);   //printing stop time





return 0;
}
