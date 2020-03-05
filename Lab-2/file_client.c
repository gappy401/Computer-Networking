#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 50

main()
{
int sockfd,retval;
char rec[MAXSIZE];
//int x=9;
char reaaa[1000];
int s=0;
int f;

int recedbytes,sentbytes;
struct sockaddr_in serveraddr;
char buff[MAXSIZE];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==-1)
{
printf("\nSocket Creation Error");

}
char a[1];
printf("%i",sockfd);
printf("\n");
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(6793);
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
if(retval==-1)
{
printf("Connection error");

}

printf("enter the  file name text\n");

scanf("%s",buff);



sentbytes=send(sockfd,buff,sizeof(buff),0);

if(sentbytes==-1)
{
printf("!!");
close(sockfd);
}
recedbytes=recv(sockfd,buff,sizeof(buff),0);
char search[200];
puts(buff);
printf("\n");
printf("which of the follwing functions do you want to perform oh the file? \n1.Read \n2.Search \n3.Replace numbers with alphabets \n4.Sort \n");
scanf("%s",a);
sentbytes=send(sockfd,a,sizeof(a),0);
int success=0;
switch(a[0])
{
   case '1': while(1)
{
     recedbytes=recv(sockfd,&f,sizeof(int),0);
  //printf("%d",f);
   if(f==1)
   {
      goto exit;
   }
   recedbytes=recv(sockfd,reaaa,1000*sizeof(char),0);
   printf("%s",reaaa);


}
exit:;; break;
   case'2': printf("%s","Write word to be searched:");
             scanf("%s",search);
             int count;
             sentbytes=send(sockfd,search,sizeof(search),0);
             recedbytes=recv(sockfd,&count,sizeof(int),0);
            printf("%s","Number of occurences are:");
             printf("%d",count);
            

   case'3':  recedbytes=recv(sockfd,&s,sizeof(int),0); 
   if(s==1)
   {
   printf(" All numbers in the file have been replace by NUM");
   }
   break;
   case'4': recedbytes=recv(sockfd,&s,sizeof(int),0); 
   if(s==1)
   {
      printf("The file has been sorted! ");

   }
   break;

}




close(sockfd);
}
