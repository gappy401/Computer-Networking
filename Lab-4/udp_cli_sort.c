#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
main()
{
int s,r,recb,sntb,x;
int sa;
socklen_t len;
printf("INPUT port number: ");
scanf("%d", &x);
struct sockaddr_in server,client;
int buff[5];
s=socket(AF_INET,SOCK_DGRAM,0);
if(s==-1)
{
printf("\nSocket creation error.");
exit(0);
}
printf("\nSocket created.");
server.sin_family=AF_INET;
server.sin_port=htons(x);
server.sin_addr.s_addr=inet_addr("127.0.0.1");
sa=sizeof(server);
len=sizeof(server);
while(1){
printf("\n\n");
int b=0,m;
printf("Enter nuber of integers in array");
scanf("%d", &b);
int y;
for(m=0;m<b;m++)
{
    scanf("%d",&buff[m]);
    

}
sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr *)&server, len);
if(sntb==-1)
{
close(s);
printf("\nMessage sending Failed");
exit(0);
}
for(m=0;m<b;m++)
{
    printf("%d",buff[m]);

}



recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr *)&server,&sa);
if(recb==-1)
{
printf("\nMessage Recieving Failed");
close(s);
exit(0);
}
printf("\nMessage Recieved: ");
int x=0;
for(x=0;x<sizeof(buff);x++)
printf("%d", buff[x]);

}
close(s);
}