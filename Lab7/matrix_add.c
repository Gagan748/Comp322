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
unsigned int num;
char buf[5];
for( i=0;i<cb.aio_nbytes;i+=4)
{
memset(buf,0,5);
memcpy(buf,cb.aio_bytes+i,4);
num=strol(buf,NULL,10);
num=num+scalar;
sprintf(buf,"%4d",num); /*coverting the char read from buf to long int and writing back to buffer for write operation*/
memcpy(cb.aio_buf+i,buf,4);
}
}

int main(int argc , char *argv[])
{
int i,j;
int scalar;
int b_offset;

scalar=rand(); 
printf("\nscalar is %d",rand);
clock_t start, stop;
int in_file,out_file;
int *buf;
int size, blocks,block_size;
if(argc<3)
{
fprintf(stderr,"\nNot sufficient input");
exit(EXIT_FAILURE);
}

size=argv[1][0]-'0';
blocks=argv[2][0]-'0';
block_size=size/blocks;
buf=(int*)malloc(block_size*block_size*(sizeof(int)));

start=clock();

struct aiocb last,current,next;

/*Control block for stdin reading*/
current.offset=0;
current.fildes=STDIN_FILENO;
memset(&current,0,sizeof(struct aiocb));
current.aio_offset=0;
current.aio_nbytes=block_size;
current.aio_buf=malloc(block_size);

/*reading first block*/
aio_read(&current);

while(aio_error(&current)==EINPROGRESS);
aio_return(&current);


/*intializing aio control blocks*/

next.aio_fildes=STDIN_FILENO;
next.aio_nbytes=block_size;
next.aio_buf=malloc(block_size);

last.aio_fildes=STDOUT_FILENO;
last.aio_offset=0;
last.aio_nbytes=block_size;
last.aio_buf=malloc(block_size);

if(!next.aio_buf || !last.aio_buf)
printf("\nunable to intialize buf to control block cb");

for(i=0;i<blocks;i++)
{
for(j=0;j<blocks;j++)
{
//memset(&next,0,sizeof(struct aiocb));
next.aio_offset=(inptr_t)-1;

aio_read(&next);
while(aio_error(&next)==EINPROGRESS);

matrix_add(&current,block_size,scalar);

memcpy(&last,&current,sizeof(struct aiocb));

aio_write(&last);
while(aio_error(&last)==EINPROGRESS);
aio_return(&last);

memcpy(&current,&next,sizeof(struct aiocb));
}
}
 
/*writing last block copied to current to STDOUT*/
matrix_add(&current,block_size,scalar);
aio_write(&current);
while(aio_error(&current)==EINPROGRESS);
aio_return(&current);

stop=clock();
double total_time=((double)(stop-start))/CLOCKS_PER_SEC;
printf("\ntotal time taken=%f",total_time);

}
