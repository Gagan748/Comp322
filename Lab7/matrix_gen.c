#include<stdio.h>
#include<stdlib.h>

int main(int argc , char *argv[])
{
int i,j,n;
unsigned int upper, lower;
upper=100;
lower=-100;
n=atoi(argv[1]);  //converting argv[1] to int
for(i=0;i<n;i++)
{
for(j=0;j<n;j++)
{
fprintf(stdout,"%4d",(rand()%(upper-lower+1))+lower);
}

printf("\n");
}
}


