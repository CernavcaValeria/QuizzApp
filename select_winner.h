unsigned int sesiune_joc;
char* select_winner()
{

 char sql[95];
 char login_winner[50];
 int rc_descriptor;
 char column_of_name[50];
 sqlite3_stmt* lg;

 bzero(login_winner, strlen(login_winner));
 

 sprintf(sql,"SELECT Name_client FROM Score WHERE id_serie=%d ORDER BY punctaj DESC LIMIT 1;",sesiune_joc);
 
rc_descriptor=sqlite3_prepare_v2(bd_global,sql, -1, &lg,0 );
 if(rc_descriptor!=SQLITE_OK)
   {
      fprintf(stderr,"Eroare la extragerea castigatorului din BD : %s \n",sqlite3_errmsg(bd_global));
   }
rc_descriptor=sqlite3_step(lg);

   
  if( rc_descriptor==SQLITE_ROW)
  {
     bzero (login_winner, strlen(login_winner));
         
        sprintf(login_winner, "%s\n",sqlite3_column_text(lg, 0));
    
  }

sqlite3_finalize(lg);
printf("#select winner# castigatorul este %s\n\n",login_winner);
   return strdup(login_winner);

}