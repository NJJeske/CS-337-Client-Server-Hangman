#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <time.h>

typedef struct info
{
  char* phrase;
  char* hint;
}info;




int main(int args, char* argv[])
{
  FILE* fin;
  char* BUFFER = (char*)malloc(sizeof(char)* 1024);
  char* token;
  info* infos = (info*)malloc(sizeof(info) * 1024);

  srand(time(NULL));
  int randomIndex = rand() % 12;

  int i = 0;
  while(!infos)
  {
  infos[i].phrase = NULL;
  infos[i].hint = NULL;
  i++;

  }

  fin = fopen("phrase.txt","r");
  if ( fin == NULL )
  {
    printf("\nFile could not be opened\n");
    exit(1);
  }
  else
  {
    struct sigaction newsig;
    struct sigaction oldsig;
    newsig.sa_flags = 0;
    sigaction(SIGINT, &newsig, &oldsig);

    int confd;
    int listfd;

    int count = 0;
    while(fgets(BUFFER, 1024, fin))
    {
    token = strtok(BUFFER, " ");
    infos[count].phrase = strdup(token);
    token = strtok(NULL, " ");
    infos[count].hint = strdup(token);
    count++;
    }

    listfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(listfd == -1)
        exit(1);

    struct sockaddr serName = {AF_UNIX, "Server"};
    socklen_t serLen = sizeof(struct sockaddr) + 6;
    bind(listfd, &serName, serLen);

    listen(listfd, 10);
    printf("Running...running...\n");

    if((confd = accept(listfd, NULL, NULL)) != -1)
    {

    write(confd, infos[randomIndex].phrase, strlen(infos[randomIndex].phrase));
    write(confd, " ", strlen(" "));
    write(confd, infos[randomIndex].hint, strlen(infos[randomIndex].hint));

    close(confd);
    unlink("Server");
    }

  fclose(fin);


  sigaction(SIGINT, &oldsig, NULL);
  }

  free(infos);
  return 0;
}



