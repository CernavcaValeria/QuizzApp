void send_msg_winner(char* who_is_winner,int sd_cl)
{
  int rez_of_send;
  unsigned int index = 0;
  char ch;
  unsigned int nr_car;
  nr_car = strlen(who_is_winner);

  clock_t begin, end;
  float time_r;
  
 send(sd_cl, &nr_car, sizeof(nr_car), 0);

 for(index=0; index<nr_car; index++)
  {
    ch = who_is_winner[index];
    send(sd_cl,&ch, 1, 0);
  }
  printf("#ssend mesage winner# castigatorul este %s\n",who_is_winner);

 // bzero(who_is_winner, strlen(who_is_winner));
}