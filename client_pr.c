#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int port;
void client_logare(int, char*);
void send_question_to_server(char*,int);
void receive_question(int);
char answer_for_question(int);
void if_the_answ_is_correct(int);
void recv_who_is_winner(int);


int main(int argc, char* argv[])
{
     int sockd_cl;
     struct sockaddr_in server;
     int nr=0;
     char buf[10];
     char nume_client[20];
     port=atoi(argv[2]);

  if (argc != 3)
    {
      printf ("~Client~: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

sockd_cl = socket (AF_INET, SOCK_STREAM,0);
   if (sockd_cl==-1)
    {
      perror ("~CLIENT~ :Eroare la socket().\n");
      return errno;
    }
  /*familia de socket*/
 server.sin_family = AF_INET;
 server.sin_addr.s_addr=inet_addr(argv[1]);;
 server.sin_port =htons(port);

 if (connect (sockd_cl, (struct sockaddr *)&server,sizeof(struct sockaddr)) == -1)
    {
      perror ("~CLIENT~: Eroare la connectare.\n");
      return errno;
    }  
  
    printf ("~CLIENT~: Introduceti un nume: ");
    fflush (stdout);
    scanf("%s", nume_client);
    client_logare(sockd_cl, nume_client);

  system("clear");
////////////////////////////////////////////////////
    printf("Doriti sa propuneti o intrebare? (Rapunde cu y sau n)\n");
    char give_question[1];
    scanf("%s", give_question);
    send(sockd_cl,&give_question, sizeof(give_question), 0);

  if(strncmp("y", give_question, 1)==0)
    { 
      printf("~Client~:Intrebarea trebuie sa fie de forma: <numar> , '<intrebarea>+?' , '<var_rs1>' , '<var_rs2>' , '<var_rs3>' , '<var_rs4>', <nr_variantei_corecte> \n");
      char client_question[300];
      scanf("%s", client_question);
      printf("CHECK:Intrebarea ta suna asa:\n %s\n",client_question);
      
      send_question_to_server(client_question,sockd_cl);
    }
  else if(strncmp("n", give_question, 1)==0)
    {
      printf("~Client~:Nu doresti sa trimiti intrebare!\n");
    }
     system("clear");
//////////////////////////////////////////////////////////
for(int k=0;k<5;k++)
{
     receive_question(sockd_cl);
    answer_for_question(sockd_cl);
    if_the_answ_is_correct(sockd_cl);
} 
    recv_who_is_winner(sockd_cl);


close(sockd_cl);
  
}//endMAIN

 
void client_logare(int sd,char *nume_client)
{
    int index;
    int lungime_nume = strlen(nume_client);
    char caracter_nume;

    send(sd, &lungime_nume, sizeof(lungime_nume), 0);

  for(index = 0; index<lungime_nume;index++)
    {
      caracter_nume = nume_client[index];
      send(sd, &caracter_nume, 1, 0);
    }
   printf("~CLIENT~: Am trimis loghinul la server %s\n",nume_client);
}
void send_question_to_server(char* question,int sd_serv)
{
   int rez_of_send;
   unsigned int index = 0;
   char ch;
   unsigned int nr_car;
   nr_car = strlen(question);
   send(sd_serv, &nr_car, sizeof(nr_car), 0);

   
  for(index=0; index<nr_car; index++)
  {
    ch = question[index];
    send(sd_serv,&ch, 1, 0);
  }
  bzero(question, strlen(question));

}

void receive_question(int sd_serv)
{

  char buf_for_question[1000];
  char byte;
  int index=0;
  unsigned int nr_car=0;
  
  recv(sd_serv, &nr_car, sizeof(nr_car), 0);
  printf("sunt in receive ckient\n");

for(index = 0; index<nr_car; index++)
  {
    recv(sd_serv, &byte, 1, 0);
    buf_for_question[index] = byte; 
  }
  buf_for_question[nr_car] = '\0';
  
  printf("\nIntrebarea primita este:\n %s\n",buf_for_question); 
} 

char answer_for_question(int sd_serv)
{
  char answ;
  time_t begin, end;  float time_r;


  printf("*** [Raspundeti cu una din cifrele 1,2,3,4] ***\n");
  getchar();
  
  time(&begin);
  answ = getchar();
  time(&end);
  
  time_r = difftime(end, begin);
  //read (0, &answ, sizeof(answ));
  printf("Timpul de rs a clientului  raspuns este %f \n", time_r);

  send(sd_serv,&answ,sizeof(answ),0);
  if(answ=='q'){  close(sd_serv); exit(EXIT_FAILURE); }
  
}
void if_the_answ_is_correct(int sd_serv)
{
  char buffer[50];
  char byte;
  int index=0;
  unsigned int nr_car=0;
  recv(sd_serv, &nr_car, sizeof(nr_car), 0);
  
for(index = 0; index<nr_car; index++)
  {
    recv(sd_serv, &byte, 1, 0);
    buffer[index] = byte; 
  }
  buffer[nr_car] = '\0';
  printf("%s\n",buffer);
  sleep(3);
  system("clear");
  
}

void recv_who_is_winner(int sd_serv)
{
  char buffer[50];
  char byte;
  int index=0;
  unsigned int nr_car=0;
  recv(sd_serv, &nr_car, sizeof(nr_car), 0);
  
for(index = 0; index<nr_car; index++)
  {
    recv(sd_serv, &byte, 1, 0);
    buffer[index] = byte; 
  }

  buffer[nr_car] = '\0';
  
  printf("Castiatorul este: %s\n",buffer);
 // bzero ( &buffer,sizeof(buffer));

}