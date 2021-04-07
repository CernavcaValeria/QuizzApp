void send_question(char* quest, int sd_cl)
{ printf("flag sunt in send question\n");
   int rez_of_send;
   unsigned int index = 0;
   char ch;
   unsigned int nr_car;
   nr_car = strlen(quest);
   send(sd_cl, &nr_car, sizeof(nr_car), 0);

   
  for(index=0; index<nr_car; index++)
  {
    ch = quest[index];
    send(sd_cl,&ch, 1, 0);
  }
 // bzero(quest, strlen(quest));

}
