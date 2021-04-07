void update_punctaj(char rs_cl,char rs_correct, char* login, int sd_cl)
{
printf("Raspunsul clientului: %c|\n", rs_cl);
printf("________________________\n\n");
printf("loghinul la care ii facem update %s \n",login);
if(rs_cl==rs_correct)
{

//________________________________
  char* str="Raspuns CORECT !\n";
  int rez_of_send;
  unsigned int index = 0;
  char ch;
  unsigned int nr_car;
  nr_car = strlen(str);

 send(sd_cl, &nr_car, sizeof(nr_car), 0);

 for(index=0; index<nr_car; index++)
  {
    ch = str[index];
    send(sd_cl,&ch, 1, 0);
  }
//_________________________________

  char sql[100];
  int rc_descriptor;
  char* zErrMsg=0;
  sprintf(sql,"UPDATE Score set punctaj=punctaj+1 WHERE Name_client='%s' ; ",login);

rc_descriptor=sqlite3_exec(bd_global,sql,NULL,0,&zErrMsg);

		if( rc_descriptor!=SQLITE_OK )
		{
			printf("SQL error \n ");
			sqlite3_free(zErrMsg);
		}
//printf("endif\n");
}
else 
{
  //printf("chesck: s-a trimis daca e corect sau nu");
  char* str="Raspuns GRESIT !\n";
  int rez_of_send;
  unsigned int index = 0;
  char ch;
  unsigned int nr_car;
  nr_car = strlen(str);

 send(sd_cl, &nr_car, sizeof(nr_car), 0);

 for(index=0; index<nr_car; index++)
  {
    ch = str[index];
    send(sd_cl,&ch, 1, 0);
  }
}
}