#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>


int main(int args, char* argv[])
{
  char* token;
  int confd;
  int soccer;
  char BUFF[20];
  char* phrase;
  char* hint;
  char input;
  int length, i, string;
  int answer;

  struct sockaddr serName = {AF_UNIX, "Server"};
  socklen_t serLen = sizeof(struct sockaddr) + 6;

  soccer = socket(AF_UNIX, SOCK_STREAM, 0);

  confd = connect(soccer, &serName, serLen);

  read(soccer, BUFF, sizeof(BUFF));

  token = strtok(BUFF," ");
  phrase = strdup(token);
  token = strtok(NULL, " ");
  hint = strdup(token);

  length = strlen(phrase);
  char* hiddenPhrase = (char*)malloc(sizeof(char) * length);


  for(i = 0; i < length; i++)
  {
  hiddenPhrase[i] = '?';
  hiddenPhrase[length] = '\0';
  }


  printf("Hint: %s\n", hint);

  while(strcmp(phrase, hiddenPhrase) != 0)
  {
  answer = 0;
  printf("Common Phrase\n");
  printf("-------------\n");
  printf("%s\n", hiddenPhrase);

   do
   {
    printf("Enter a single character guess : ");
    scanf("%s", &input);
    string = strlen(&input);

    if(string == 1)
    {
    answer = 1;
    }

   } while(answer != 1);

   int j;
   for (j = 0; j < length; j++)
   {
    if (phrase[j] == input)
    {
   hiddenPhrase[j] = input;

    }
   }

  }
  printf("\n%s\n", hiddenPhrase);
  printf("\nYou Win!\n");
  close(confd);
  close(soccer);
  unlink("Server");

  return 0;

}
