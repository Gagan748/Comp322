#include<stdio.h>

int main(int argc , char *argv[])
{
unsigned long page;
unsigned long offset;
unsigned long address;

address=atoll(argv[1]);

page=address>>12;
offset= address & 0xfff;
printf("The address %lu contains:\n",address);
printf("Page number=%lu\n",page);
printf("offset=%lu\n",offset);

return 0;
}

