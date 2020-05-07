#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

int main(int argc , char *argv[])
{
char *s;
FILE *logfile=fopen("lab6.log","a");
if(logfile!=0)
{
if(argc>1 && strcmp(argv[1],"1")==0)
s="Pop Mole1";
else
s="Pop Mole2";
fprintf(logfile,"\n%s",s);
fclose(logfile);
}
}
