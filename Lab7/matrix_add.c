#include<sys/types.h>
#include<aio.h>
#include<errno.h>
#include<stdio.h>
#include<fcntl.h>
#include<time.h>
#include<malloc.h>
#include<unistd.h>
#include<stdlib.h>
//typedef struct aiocb aiocb_t;
void matrix_add(struct aiocb *cb, int size, int scalar)
{
int i;
unsigned int value;
char buf[5];
for( i=0;i<cb->aio_nbytes;i+=4)
{
memset(buf,0,5);
memcpy(buf,(void *)cb->aio_nbytes+i,4);
value=strtol(buf,NULL,10);
value=value+scalar;
printf("%4d",value);
sprintf(buf,"%4d",value); /*coverting the char read from buf to long int and writing back to buffer for write operation*/
memcpy((void *)cb->aio_buf+i,buf,4);
}
printf("\n");
}

int main(int argc , char *argv[])
{
int i,j;
int scalar;
int b_offset;

scalar=rand()%200; 
printf("\nscalar is %d",scalar);
clock_t start, stop;

int size, blocks,block_size,total_size;
if(argc<3)
{
fprintf(stderr,"\nNot sufficient input");
exit(EXIT_FAILURE);
}

size=atoi(argv[1]);
blocks=atoi(argv[2]);
if(size%blocks !=0)
{
fprintf(stderr,"\nBlocks can't divide the whole matrix");
exit(EXIT_FAILURE);
}
total_size=size*size;
block_size=size/blocks;

//buf=(int*)malloc(block_size*block_size*(sizeof(int)));
printf("\n matrix size=%d, blocks=%d blocksize=%d",size,blocks,block_size);
start=clock();

struct aiocb last,current,next;
int ret1,ret2;
/*Control block for stdin reading*/
memset(&current,0,sizeof(struct aiocb));
memset(&last,0,sizeof(struct aiocb));
memset(&next,0,sizeof(struct aiocb));

current.aio_offset=0;
current.aio_fildes=0;   //to read STDIN
current.aio_nbytes=4*block_size*block_size;
current.aio_buf=malloc(4*block_size*block_size);

/*reading first block*/
aio_read(&current);

while(aio_error(&current)==EINPROGRESS);
ret1=aio_return(&current);
//if(ret1>=0)
//printf("\n reading offirst block done");


/*intializing aio control blocks*/

next.aio_fildes=0;  //to read STDIN;
next.aio_nbytes=4*block_size*block_size;
next.aio_buf=malloc(4*block_size*block_size);
next.aio_offset=0;

last.aio_fildes=1; //to write to STDOUT
last.aio_offset=0;
last.aio_nbytes=4*block_size*block_size;
last.aio_buf=malloc(4*block_size*block_size);

if(!next.aio_buf || !last.aio_buf)
printf("\nunable to intialize buf to control block cb");

next.aio_offset=current.aio_nbytes; //first nbytes read by current block already
//printf("\n offset of next block now is %d",(int*)next.aio_offset);
for(i=0;i<blocks;i++)
{
for(j=0;j<blocks;j++)
{
//memset(&next,0,sizeof(struct aiocb));;
if(next.aio_offset>=total_size)
{
//printf("\nAll bytes read");
return;
}
next.aio_fildes=0; //setting to read input
aio_read(&next);
while(aio_error(&next)==EINPROGRESS);
ret1=aio_return(&next);
//if(ret1>=0)
//printf("\nreading of next done");
//matrix_add(&current,block_size,scalar);

memcpy(&last,&current,sizeof(struct aiocb));
last.aio_fildes=1;
last.aio_offset=0;

aio_write(&last);
while(aio_error(&last)==EINPROGRESS);
ret2=aio_return(&last);
//if(ret2>=0)
//printf("\n writing done");
memcpy(&current,&next,sizeof(struct aiocb));
next.aio_offset=next.aio_offset+next.aio_nbytes;
//printf("\n next_offset =%d ", (int*)next.aio_offset);
}
}
 
/*writing last block copied to current to STDOUT*/
//matrix_add(&current,block_size,scalar);
current.aio_fildes=1;
aio_write(&current);
while(aio_error(&current)==EINPROGRESS);
aio_return(&current);

stop=clock();
double total_time=((double)(stop-start))/CLOCKS_PER_SEC;
printf("\ntotal time taken=%f",total_time);

}
