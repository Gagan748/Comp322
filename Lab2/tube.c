#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

const int READ=0, WRITE=1;

int main(int argc, char *argv[])
{
 pid_t pid1, pid2;
 int fd[2];
char *args1[argc],*args2[argc];   //creating args array for first and second command 
 
int i,k=0;
int status1, status2;
for(i=1;i<argc;i++)
{
if(argv[i]!=NULL && strcmp(argv[i],",")==0)
break;
args1[k]=argv[i];
k++;
}
args1[k]=NULL;

int j,l;

if(argv[i]!=NULL)
{
i++;
l=0;
for(j=i;j<argc;j++)
{
args2[l]=argv[j];
l++;
}
args2[l]=NULL;
}
if(pipe(fd)==-1)
fprintf(stderr, "Pipe failed");

//creating first child
pid1=fork();
if(pid1==0)
{
//child 1 process running
close(fd[READ]);  //closing read end of pipe while child 1 writes to pipe
dup2(fd[WRITE],WRITE);  //tie std out of child 1 to write end of pipe
if(execve(args1[0],args1,NULL)==-1) //executing first command
printf("\n error in child1 runnning");
return 0;
}
else if(pid1>0) //parent running
{

pid2=fork();//creating child 2
if(pid1>0 && pid2>0)  //only parent is running
{
fprintf(stderr,"\n%s: $$=%d",args1[0],pid1);
fprintf(stderr,"\n%s $$:=%d\n",args2[0],pid2);
}
if(pid2==0)  //child 2 running
{
close(fd[WRITE]);   //close write end of pipe while child 2 reads from pipe
dup2(fd[READ],READ);   //tie read end of pipe to std input of child 2
if(execve(args2[0],args2,NULL)==-1)  //executing second set of arguments
printf("\n error in child 2 running");
return 0;

}
waitpid(pid1,&status1,0);  //waiting for child 1 to finish
close(fd[1]);  //closing write end of second command
waitpid(pid2,&status2,0);//waitinf for child 2 to finish
fprintf(stderr,"%s: $?=%d",args1[0],status1);
fprintf(stderr,"\n%s: $?=%d\n",args2[0],status2);
return 0;
}
}

