char* select_current_serie(char*login)
{
char nr_serii[20];
 char sql[100];
 int rc_descriptor;
 sqlite3_stmt* lg;

 sprintf(sql,"SELECT id_serie FROM Score WHERE Name_client='%s';", login);

 rc_descriptor=sqlite3_prepare_v2(bd_global,sql, -1, &lg,0 );
 if(rc_descriptor!=SQLITE_OK)
   {
      fprintf(stderr,"Eroare la extragerea castigatorului din BD : %s \n",sqlite3_errmsg(bd_global));
   }
rc_descriptor=sqlite3_step(lg);

   
  if( rc_descriptor==SQLITE_ROW)
  {       
   sprintf(nr_serii, "%s\n",sqlite3_column_text(lg, 0));
  }

   sqlite3_finalize(lg);
   printf("numerul seriei curente : %s\n",nr_serii);
   return strdup(nr_serii);


}