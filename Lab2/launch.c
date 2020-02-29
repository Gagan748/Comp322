#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{

pid_t cpid;
cpid=fork();
int status;
if(argc<1)
{
printf("\nINVALID Input\n");
exit(EXIT_FAILURE);
}
char* args[argc];
int i;
int k=0;
for(i=1;i<=argc;i++)
{
args[k]=argv[i];
k++;
}
if(argc<2)
{
printf("INVALID input");
exit(EXIT_FAILURE);
}

if(cpid==0)
{
fprintf(stderr,"\n%s: $$ = %d\n",args[0],getpid());


execve(argv[1],args,NULL);

//}
}
else if(cpid>0)
{
waitpid(cpid,&status,0);
fprintf(stderr,"%s $: = %d\n",args[0],status);
return 0;

}
return 0;
}
