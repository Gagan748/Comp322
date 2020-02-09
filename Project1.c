#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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
if(x>=32 && x<=255 && x!=127)
printf("%c",x);

else if(x==127)
printf("DEL");

else
{
if(x==0)printf("NUL");if(x==1)printf("SOH");if(x==2)printf("STX");if(x==3)printf("ETX");if(x==4)printf("EOT");if(x==5)printf("ENQ");
if(x==6)printf("ACK");if(x==7)printf("BEL");if(x==8)printf("BS");if(x==9)printf("HT");if(x==10)printf("LF");
if(x==11)printf("VT");if(x==12)printf("FF");if(x==13)printf("CR");if(x==14)printf("SO");
if(x==15)printf("SI");if(x==16)printf("DLE");if(x==17)printf("DC1");if(x==18)printf("DC2");if(x==19)printf("DC3");if(x==20)printf("DC4");
if(x==21)printf("NAK");if(x==22)printf("SYN");if(x==23)printf("ETB");
if(x==24)printf("CAN"); if(x==25)printf("EM"); if(x==26)printf("SUB"); if(x==27)printf("ESC"); if(x==28)printf("FS"); if(x==29)printf("GS");
if(x==30)printf("RS"); if(x==31)printf("US");
}

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
printf("\n ERROR\n");
return 0;
}

if(argv[1][0]=='0' || argv[1][0]=='1' || argv[1][0]=='-')
        {

        printf("\nOriginal\t\t  Decimal\tASCII\tParity\n");
        printf("\n---------------------------------------------------------\n");


        int count=argc,k,j,dec;
        int val[8],l;
         for(j=1;j<count;j++)
           {
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
            printf("%8d\t",dec);
            printAscii(binToDec(val));
            printf("\t");
            printParity(val);
            printf("\n");
           }
        }

  else
        {
            FILE *fptr=fopen(argv[1],"r");
            if(fptr==NULL)
                {
                printf("\nInvalid file");
                exit(-1);
                }
        char ch;
        int val[8],i=0,j;

printf("\nOriginal\t\t  Decimal\tASCII\tParity\n");
        printf("\n---------------------------------------------------------\n");
        int dec;
         for(j=0;j<8;j++)
          val[j]=0;

        while((ch=fgetc(fptr))!=EOF)
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
              printf("%8d\t",dec);
              printAscii(binToDec(val));
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
                                                                   


