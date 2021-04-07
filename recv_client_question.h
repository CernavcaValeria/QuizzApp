char* recv_client_question( int sd_cl)
{
  char buf_for_question[300];
  char byte;
  int index=0;
  unsigned int nr_car=0;
  
  recv(sd_cl, &nr_car, sizeof(nr_car), 0);

for(index = 0; index<nr_car; index++)
  {
    recv(sd_cl, &byte, 1, 0);
    buf_for_question[index] = byte; 
  }
  buf_for_question[nr_car] = '\0';

 printf( "\n~Server~:Intrebarea propusa de jucator:\n%s\n",buf_for_question);
  return strdup(buf_for_question);
  
}