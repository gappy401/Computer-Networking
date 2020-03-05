#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#define MAXSIZE 90

int cfileexists(const char *filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if (exist == 0)
        return 1;
    else // -1
        return 0;
}

main()
{
    int sockfd, newsockfd, retval;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;
    char x[20] = "File exist";
    char y[40] = "Filedoes not exist,created.";
    char buff[MAXSIZE];
    //int a=0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf("\nSocket creation error");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(6793);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    retval = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (retval == 1)
    {
        printf("Binding error");
        close(sockfd);
    }

    retval = listen(sockfd, 1);
    if (retval == -1)
    {
        close(sockfd);
    }

    actuallen = sizeof(clientaddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &actuallen);

    if (newsockfd == -1)
    {
        close(sockfd);
    }

    recedbytes = recv(newsockfd, buff, sizeof(buff), 0);

    if (recedbytes == -1)
    {
        close(sockfd);
        close(newsockfd);
    }

    char *filename;
    filename = buff;

    int exist = cfileexists(filename);
    if (exist)
        sentbytes = send(newsockfd, x, sizeof(x), 0);
    else
       { sentbytes = send(newsockfd, y, sizeof(y), 0);
         FILE * fPtr;
         fPtr = fopen(filename, "w");
         fclose(fPtr);
       }


    


    char a[1];
    recedbytes = recv(newsockfd, a, sizeof(a), 0);
    printf("%ch", a[0]);
    int flag = 0;

    switch (a[0])
    {
    case '1':;
        FILE *fp = fopen(filename, "r");
        if (fp == NULL)
        {
            perror("Unable to open file!");
            exit(1);
        }

        char chunk[128];

        while (fgets(chunk, 1000 * sizeof(char), fp) != NULL)
        {
            sentbytes = send(newsockfd, &flag, sizeof(int), 0);
            //fputs(chunk, stdout);
            // trim(chunk);
            sentbytes = send(newsockfd, chunk, 1000 * sizeof(char), 0);
        }

        flag = 1;
        sentbytes = send(newsockfd, &flag, sizeof(int), 0);
        //printf("%d",flag);

        fclose(fp);
        
        break;
    case '2':;
        char search[100];
        recedbytes = recv(newsockfd, search, sizeof(search), 0);
        FILE *f = fopen(filename, "r");
        if (f == NULL)
        {
            perror("Unable to open file!");
            exit(1);
        }

        char chunks[128];

        int count = 0;
        while (fgets(chunks, 1000 * sizeof(char), f) != NULL)
        {
            char *a = strstr(chunks, search);
            if (a)
            {
                count++;
            }
        }
        flag = 1;
        sentbytes = send(newsockfd, &count, sizeof(int), 0);
        fclose(f);
        

        break;
    case '3':;int success=1;
        system("cp test.txt test.txt.tmp");

        system("sed 's/[0-9]/NUM/g' test.txt.tmp >test.txt");
        sentbytes = send(newsockfd, &success, sizeof(int), 0);
          break;
    case '4': ;int success1=1;
          system("cp test.txt test.txt.tmp");

        system("sort test.txt.tmp >test.txt");
        sentbytes = send(newsockfd, &success1, sizeof(int), 0);
        break;


    }

  
  

   if (sentbytes == -1)
  {
    close(sockfd);
    close(newsockfd);
  }

   close(sockfd);
   close(newsockfd);
}


