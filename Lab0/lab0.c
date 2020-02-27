#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>

char asc[33][6]={"NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL","BS","TAB","LF","VT","FF","CR","SO","SI","DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB","CAN","EM","SUB","ESC","FS","GS","RS","US","SPACE"};
int power(int x, int y)
{
        int temp;
        if(y==0)
        return 1;
        temp=power(x,y/2);
         if(y%2==0)
        return temp*temp;
        else
        return x*temp*temp;
}

void printParity(int a[])
{
int i,count=0;
for(i=0;i<8;i++)
{
  if(a[i]==1)
  count++;
}
if(count%2==0)
printf("EVEN");
else
printf("ODD");
}

void printAscii(int x)
{
if(x>32 && x<127)
printf("%-15c",x);

else if(x==127)
printf("%-15s","DEL");

else if(x<=32)
printf("%-15s",asc[x]);
else
printf("%-15s","man ascii");
}

void printNum(int a[], int n)
{
        int i;
        for(i=0;i<n;i++)
        printf("%d",a[i]);
        printf("\t\t");


}

int  binToDec(int a[])
{
        int num=0,k=0,i;
        for( i=7;i>=0;i--)
        {
           num=num+power(2,i)*a[k];
           k++;
        }
        return num;
}

int main(int argc , char** argv)
{
 if(argc<2)
{
printf("\nInvalid Input\n");
return 0;
}
if(argv[1][0]=='-' && argc<3)
{
printf("\n Invalid Input");
return 0;
}
if(argv[1][0]=='0' || argv[1][0]=='1' || argv[1][0]=='-')
        {

        printf("\nORIGINAL\t\tASCII\t\tDECIMAL\t\tPARITY");
        printf("\n-------------------------------------------------------------\n");


        int count=argc,k,j,dec;
        int val[8],l;
       
         for(j=1;j<count;j++)
           {
	    if(argv[j][0]=='-')
	     j++;

          for(l=0;l<8;l++)
           val[l]=0;
	  k=0;
            while(argv[j][k]!='\0')
                {
                  val[k]=argv[j][k]-'0';
                  k++;
                }
            printNum(val,8);
                              
  dec= binToDec(val);
	    printAscii(binToDec(val));

            printf("%8d\t",dec);
            printf("\t");
            printParity(val);
            printf("\n");
           }
        }

  else
        {
            int fd=open(argv[1],O_RDONLY);
            if(fd==-1)
                {
                printf("\nInvalid file\n");
                return 0;
                }
        char ch;
        int val[8],i=0,j;

printf("\nORIGINAL\t\tASCII\t\tDECIMAL\t\tPARITY");
        printf("\n-------------------------------------------------------------\n");
        int dec;
         for(j=0;j<8;j++)
          val[j]=0;

        while((read(fd,&ch,1))!=0)
             {
             if(ch=='0' || ch=='1')
             {
             val[i]=ch-'0';
             i++;
             }

           else if(i==0 && (ch!='0' || ch!='1'))
              continue;
            else  if((i%8)==0 || ch==' ' || ch=='\n')
            {  
              printNum(val,8);
                                       
               dec=binToDec(val);
             printAscii(binToDec(val));
              printf("%8d\t",dec);
              printf("\t");
              printParity(val);
              printf("\n");

             for(j=0;j<8;j++)
             val[j]=0;
             i=0;


             }
        }
        }
return 0;
}
                                                                   


