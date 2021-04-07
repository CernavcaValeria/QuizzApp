char receive_answ(int sd_cl)
{
  char answ;
  clock_t begin, end;
  float time_r;

  begin = clock();
  recv(sd_cl,&answ,sizeof(answ),0);
  end = clock();
  time_r = ((float)(end - begin))/CLOCKS_PER_SEC;
  printf("Timpul de rs a clientului  raspuns este %f \n", time_r);
 // printf("raspunsul este %c\n",answ);
  return answ;
}