#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<signal.h>
#include<unistd.h>
#include<sys/resource.h>
//#include"stderr.h"

static pid_t pid_child,pid;
static int num;

void handler(int signum)
{
if(signum==SIGTERM)
{
fprintf(stderr,"\nsend SIGTERM to %d",(int)pid_child);
kill(pid_child,SIGTERM);
//kill(pid, SIGTERM);
printf("\nexiting daemon");
exit(0);
}
else if(signum==SIGUSR1)
{
if(num==0 && pid_child>0)
{
printf("\nSend SIGCHLD to %d",(int)pid_child);
kill(pid_child,SIGCHLD);
}
num=rand()%2;
char snum[10];
sprintf(snum,"%d",num+1);
char *args[]={"mole",snum,0};
pid_child=fork();
if(pid_child==0)
{
fprintf(stderr,"\nabout to execute %s %s",args[0],args[1]);
execv(args[0],args);
fprintf(stderr,"\nfailed(1) to exceute %s %s",args[0],args[1]);
}
signal(SIGUSR1,handler);
}
else if(signum==SIGUSR2)
{
if(num==1)
{
fprintf(stderr,"\nsend SIGCHLD to %d",(int)pid_child);
kill(pid_child,SIGCHLD);
}
num=rand()%2;
char snum[10];
sprintf(snum,"%d",num+1);
char *args[]={"mole",snum,0};
pid_child=fork();
if(pid_child==0)
{
fprintf(stderr,"\nabout to execute %s %s",args[0],args[1]);
execv(args[0],args);
fprintf(stderr,"\nfailed (2) to execute %s %s",args[0],args[1]);
}
signal(SIGUSR1,handler);
}
else
fprintf(stderr,"\nreceived unexpected signal %d",signum);
}


int main(int argc, char *argv[])
{
int fd0,fd1,fd2;
 pid=fork();
if(pid<0)
fprintf(stderr,"\nfork failed");
if(pid>0)
{
fprintf(stderr,"\nPID of child1 process is %d\n",pid);
exit(EXIT_FAILURE);
}
umask(0);
/*set new session */
pid_t sid=setsid() ;
/*if(chdir("/")<0)
fprintf(stderr,"\nDirectory cant be changed to root");
*/
if(sid<0)
{
fprintf(stderr,"\nsetsid() failed");
exit(EXIT_FAILURE);
}
struct rlimit lim;
if(getrlimit(RLIMIT_NOFILE,&lim)<0)
fprintf(stderr,"\ncant get file limits");

if(lim.rlim_max==RLIM_INFINITY)
lim.rlim_max=1024;

int x;
/*closing all File decriptors*/
for(x=0;x<lim.rlim_max;x++)
close(x);
/*opening standard file descriptors and mapping to /dev/nulll
 * A file descriptor can take values 0,1,2 if stdin, stdout, stderr are closed and new fd takes the value of least available fd number. */

fd0=open("/dev/null",O_RDWR);  //value 0 for STDIN
fd1=dup(0);                 //value 1 for STDOUT
fd2=dup(0);                 //value 2 for STDERR
signal(SIGTERM, handler);
signal(SIGUSR1, handler);
signal(SIGUSR2,handler);

pid_child=fork();
while(1)
{
sleep(1);
fprintf(stderr,"\nin while");
if(pid_child==0)
{
num=rand()%2;
char snum[2];  //to store num as character
sprintf(snum,"%d",num+1);  //stored as mole 1 or mole 2
char *args[]={"mole",snum,0};
printf("\n about to execute child %s \n ",args[1]);
execv(args[0],args);
printf("\nfailed to execute %s",args[1]);
}
}
return 0;
}


