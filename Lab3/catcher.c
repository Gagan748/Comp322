#include<stdio.h>
#include<signal.h>  //for signal()
#include<unistd.h>   //to execute pause()
#include<time.h> //to execute time()
#include<stdlib.h>
#include<string.h>

//character array with all signal names as strings to be printed
int sig_int_flag;
char *signame[34]={"null","SIGUP","SIGINT","SIGQUIT","SIGILL","SIGTRAP","SIGABRT","SIGBUS","SIGFPE","SIGKILL","SIGUSR1","SIGSEGV","SIGUSR2","SIGPIPE","SIGARLRM","SIGTERM","SIGSTKFLT","SIGCHLD","SIGCONT","SIGSTOP","SIGTSTP","SIGTTIN","SIGTTOU","SIGURG","SIGXCPU","SIGXFSZ","SIGVTALRM","SIGPROF","SIGWINCH","SIGIO","SIGPWR","SIGSYS"};

//function returning integer value corresponding to signal
int signo(char *str)
{
if(strcmp(str,"UP")==0)return 1; if(strcmp(str,"INT")==0) return 2;
if(strcmp(str,"QUIT")==0)return 3; if(strcmp(str,"ILL")==0)return 4;
if(strcmp(str,"TRAP")==0)return 5;if(strcmp(str,"ABRT")==0)return 6;
if(strcmp(str,"BUS")==0)return 7;if(strcmp(str,"FPE")==0)return 8;
if(strcmp(str,"KILL")==0)return 9;if(strcmp(str,"USR1")==0)return 10;
if(strcmp(str,"SEGV")==0)return 11;if(strcmp(str,"USR2")==0)return 12;
if(strcmp(str,"PIPE")==0)return 13;if(strcmp(str,"ALRM")==0)return 14;
if(strcmp(str,"TERM")==0)return 15;if(strcmp(str,"STKFLT")==0)return 16;
if(strcmp(str,"CHLD")==0)return 17;if(strcmp(str,"CONT")==0)return 18;
if(strcmp(str,"STOP")==0)return 19;if(strcmp(str,"TSTP")==0)return 20;
if(strcmp(str,"TTIN")==0)return 21;if(strcmp(str,"TTOU")==0)return 22;
if(strcmp(str,"URG")==0)return 23;if(strcmp(str,"XCPU")==0)return 24;
if(strcmp(str,"XFSZ")==0)return 25;if(strcmp(str,"VTALRM")==0)return 26;
if(strcmp(str,"PROF")==0)return 27;if(strcmp(str,"WINCH")==0)return 28;
if(strcmp(str,"IO")==0)return 29;if(strcmp(str,"PWR")==0)return 30;
if(strcmp(str,"SYS")==0)return 31;
return -1;
}
int signo1(char *str)
{
if(strcmp(str,"SIGUP")==0)return 1; if(strcmp(str,"SIGINT")==0) return 2;
if(strcmp(str,"SIGQUIT")==0)return 3; if(strcmp(str,"SIGILL")==0)return 4;
if(strcmp(str,"SIGTRAP")==0)return 5;if(strcmp(str,"SIGABRT")==0)return 6;
if(strcmp(str,"SIGBUS")==0)return 7;if(strcmp(str,"SIGFPE")==0)return 8;
if(strcmp(str,"SIGKILL")==0)return 9;if(strcmp(str,"SIGUSR1")==0)return 10;
if(strcmp(str,"SIGSEGV")==0)return 11;if(strcmp(str,"SIGUSR2")==0)return 12;
if(strcmp(str,"SIGPIPE")==0)return 13;if(strcmp(str,"SIGALRM")==0)return 14;
if(strcmp(str,"SIGTERM")==0)return 15;if(strcmp(str,"SIGSTKFLT")==0)return 16;
if(strcmp(str,"SIGCHLD")==0)return 17;if(strcmp(str,"SIGCONT")==0)return 18;
if(strcmp(str,"SIGSTOP")==0)return 19;if(strcmp(str,"SIGTSTP")==0)return 20;
if(strcmp(str,"SIGTTIN")==0)return 21;if(strcmp(str,"SIGTTOU")==0)return 22;
if(strcmp(str,"SIGURG")==0)return 23;if(strcmp(str,"SIGXCPU")==0)return 24;
if(strcmp(str,"SIGXFSZ")==0)return 25;if(strcmp(str,"SIGVTALRM")==0)return 26;
if(strcmp(str,"SIGPROF")==0)return 27;if(strcmp(str,"SIGWINCH")==0)return 28;
if(strcmp(str,"SIGIO")==0)return 29;if(strcmp(str,"SIGPWR")==0)return 30;
if(strcmp(str,"SIGSYS")==0)return 31;
return -1;
}

static int term=0;
static int count=0;
void my_handler(int sig)
{
time_t seconds;
time(&seconds); //giving present time
signal(sig,my_handler); //registering signal handler again
fprintf(stdout,"%s signal caught at %d\n ",signame[sig],seconds);
count++;  //counting number of signals caught
}



int main(int argc, char *argv[])
{
//printing PID of process
 fprintf(stderr,"catcher: $$ = %d\n",getpid());
int i=1,sig;
int j;

//calling signal handler for all the arguments
for(i=1;i<argc;i++)
{
//registering handler for all signal before reading the one in arguments
for(j=1;j<32;j++)
{
sig=signo1(signame[j]); //sig gives corresponding integer value to signal
signal(sig,my_handler);
}

sig=signo(argv[i]);  //calculating integer value for signal in argument
if(signal(sig, my_handler)==SIG_ERR)  //install a signal handler
printf("can't catch signal %s\n",argv[0]);//if there's error while installing
pause();  // waiting for a signal
}

for(i=0;i<3;i++) //this catches 3 more signals before the program terminates(here TERM)
pause(); //waiting for a signal( 3 times)

fprintf(stderr,"Catcher: Total signal count=%d\n",count);
return 0;
}

