#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>


int main()
{
int s,r,recb,sntb,x;
int ca;
printf("INPUT port number: ");
scanf("%d", &x);
socklen_t len;
struct sockaddr_in server,client;
int buff[5];
s=socket(AF_INET,SOCK_DGRAM,0);
if(s==-1)
{
printf("\nSocket creation error.");
exit(0);
}
printf("\nSocket created.");
//printf("sup");
server.sin_family=AF_INET;
server.sin_port=htons(x);
//printf("bye");
server.sin_addr.s_addr=htonl(INADDR_ANY);
len=sizeof(client);
ca=sizeof(client);
//printf("hi");
r=bind(s,(struct sockaddr*)&server,sizeof(server));
printf("%d",r);
if(r==-1)
{
printf("\nBinding error.");
exit(0);
}
printf("kwef");
printf("\nSocket binded.");
while(1){
recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
if(recb==-1)
{
printf("\nMessage Recieving Failed");
close(s);
exit(0);
}
//printf("\nMessage Recieved: ");
//printf("%s", buff);
int l=sizeof(buff);
int i=0,j=0;
int x=0;
for(i=0;i<l-1;i++)
{
    for(j=i+1;j<l-i-1;j++)
    {
         if (buff[j] > buff[j+1])  
         {
             
             int x=buff[j+1];
             buff[j+1]=buff[j];
             buff[j]=x;
         }
           

    }
}
int m;
for(m=0;m<5;m++)
{
    printf("%d",buff[m]);

}


   sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);

	
//printf("\n\n");
//printf("Type Message: ");
//scanf("%s", buff);

if(sntb==-1)
{
printf("\nMessage Sending Failed");
close(s);
exit(0);
}

}
close(s);
}