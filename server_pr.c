#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <sqlite3.h>
#include <time.h>
#include "open_bd.h"
#include "insert_to_table.h"
#include "extract_from_bd.h"
#include "send_question.h"
#include "receive_answ.h"
#include "update_bd.h"
#include "select_winner.h"
#include "send_msg_winner.h"
#include "insert_quest_from_client.h"
#include "delete_all_players.h"
#include "recv_client_question.h"
#include "insert_intermediate_table_of_question.h"
#include "delete_all_intermediaters.h"
#include "update_to_null.h"

#define PORT 1111
extern errno;
sqlite3* bd_global;
char buf_for_question[300];
char correct_answer;
unsigned int sesiune_joc;
float suma_timp=0;
time_t begin, end;  float time_r;


static void *processing(void *);
void insert_to_table_Login(char*);
char* answer_login( void*);
char extract_from_bd(int);
void send_question(char*, int);
char receive_answ(int);
void update_punctaj(char, char,char*,int);
char* select_winner();
void send_msg_winner(char*,int);
char* recv_client_question(int);
void insert_quest_from_cl(char*);
void delete_all_players();
void insert_intermediate_table_of_question();
void delete_all_intermediaters();
void update_to_null();


typedef struct thread
{
	int idThread;
	int cl;

}thread;


int main()
{
 struct sockaddr_in my_server;
 struct sockaddr_in my_client;
 
 pthread_t th[50];  
 int k=0;
 int nr_clienti_s=0;
  
 int sockd;



 sockd = socket(AF_INET, SOCK_STREAM,0);
    if( sockd==-1)
    {
       perror ("~SERVER~: Eroare la SOCKET  ");
       return errno;
    }

  int on=1;
  setsockopt(sockd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

  bzero (&my_server, sizeof (my_server));
  bzero (&my_client, sizeof (my_client));
  
 my_server.sin_family = AF_INET;
 my_server.sin_addr.s_addr=htonl (INADDR_ANY);
 my_server.sin_port =htons(PORT);


 if ( bind(sockd, (struct sockaddr*)&my_server, sizeof(my_server)) <0 )
    {
       perror ("~SERVER~ : Eraore la BIND ");
       return errno;
    }

 if( listen(sockd,SOMAXCONN)<0)
     { 
       perror ("~SERVER~ : Eraore la LISTEN ");
       return errno;
     }

open_BD();
delete_all_players();
delete_all_intermediaters();

insert_intermediate_table_of_question();

for(; ;)
{  
	thread * td; //parametru functia executata de thread     
    int length = sizeof (my_client);
    int client;
    int lg= sizeof(my_client);

printf( "~SERVER~ : Astept la portul (%d) \n",PORT);

time(&begin);

client = accept( sockd ,(struct sockaddr*)&my_client, &lg );
time(&end);

nr_clienti_s++;
if(k==0){suma_timp=2; printf("k=%d\n", k);}
else {
   suma_timp+=difftime(end, begin);
   printf("Difftime = %f ", difftime(end, begin));
    }
    
if(suma_timp>=60 && nr_clienti_s>=2)
{
   suma_timp = 0;
   nr_clienti_s=0;

}


printf("Timpul scurs: %f \n", difftime(end, begin));
printf("Suma timp: %f \n", suma_timp);

   if(client==-1)
    {
     perror ("~SERVER~ : Eroare la accept ");
     return errno; 
    }
    printf("descriptorul de clientul curent %d\n",client);

td=(struct thread*)malloc(sizeof(struct thread));

td->idThread=k++;
td->cl=client;

pthread_create(&th[k], NULL, &processing, td);

if(suma_timp==0) 
{
   sesiune_joc++;
   insert_intermediate_table_of_question();
}

}
//endFOR

sqlite3_close(bd_global);
close(sockd);


}//endMAIN


static void *processing(void * arg)
{		

char raspuns_corect;
char question[300];
unsigned int index = 0;
char raspunsul_clientului; 
char *winner;
char *login_rec;


		struct thread td_new1; 
		td_new1= *((struct thread*)arg);	
      printf ("~THREAD~ %d - Astept mesajul...\n", td_new1.idThread);
		fflush (stdout);		 
		pthread_detach(pthread_self());



login_rec=answer_login((struct thread*)arg);

for( int k=0;k<5; k++)
{

raspuns_corect=extract_from_bd(k);
for(int count=0;count<300;count++){question[count]=buf_for_question[count];}
   
send_question(question, td_new1.cl);

raspunsul_clientului=receive_answ(td_new1.cl);
if(raspunsul_clientului=='q')
{
   update_to_null(login_rec);
   close ((intptr_t)arg);
		return(NULL);	
}
else
update_punctaj(raspunsul_clientului,raspuns_corect,login_rec,td_new1.cl);
}

winner=select_winner();
printf("Castigatorul este %s \n", winner);
send_msg_winner(winner ,td_new1.cl);



	/* am terminat cu acest client, inchidem conexiunea */
		close ((intptr_t)arg);
		return(NULL);	
}

char* answer_login(void *arg)
{ 
  unsigned int index = 0;
  char login_rec[20];
  int nr_car_login;
  char caracter_rec;
  struct thread td_new2;
  td_new2= *((struct thread*)arg);

bzero(login_rec,strlen(login_rec));

/*primesc loginul*/
recv(td_new2.cl, &nr_car_login, sizeof(nr_car_login), 0);
    for(index = 0; index<nr_car_login; index++)
    {
       recv(td_new2.cl, &caracter_rec, 1, 0);
       login_rec[index] = caracter_rec;
    }  printf("~Server~:Login-ul este: %s\n", login_rec);
    printf("descriotrul desocket este  %d\n",td_new2.cl);

insert_to_table_Login(login_rec);

/*daca clientul vrea sa propuna intrebare */////////////////////////
char answ[1];
recv(td_new2.cl,&answ,sizeof(answ),0);
if(strncmp("y", answ, 1)==0)
 {
   char* question_from_client;
   question_from_client=recv_client_question(td_new2.cl);
   insert_quest_from_cl(question_from_client);
 }
else
 { 
    printf("~Server:Clientul nu vrea sa propuna intrebari \n");
 
 }

return strdup(login_rec);

}








