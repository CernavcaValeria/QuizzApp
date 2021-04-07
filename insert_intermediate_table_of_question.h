sqlite3* bd_global;
unsigned int sesiune_joc;
void insert_intermediate_table_of_question()
{ //select
 char *zErrMsg = NULL;
 char query_extract[100];
 sqlite3_stmt* id;
 char id_q[2];

 char *zErrMsg2 = NULL;
	char query[300];
	int descriptor2;
 bzero (id_q, strlen(id_q));

for(int i=0;i<5;i++)
{
 sprintf(query_extract,"SELECT id_q FROM Question ORDER BY random() LIMIT 1;");

 int descriptor=sqlite3_prepare_v2(bd_global,query_extract, -1,&id,0 );

   if(descriptor!=SQLITE_OK)
   {
      fprintf(stderr,"Eroare la extragerea intrebarii din BD : %s \n",sqlite3_errmsg(bd_global));
   }
   

 descriptor=sqlite3_step(id);

   
  if(descriptor==SQLITE_ROW)
  {
    bzero (id_q, strlen(id_q));
     sprintf(id_q, "%s",sqlite3_column_text(id, 0));
  }//endif
   
   sqlite3_finalize(id);

//insert
  sprintf(query,"INSERT INTO Intermediate(id_serie,id_q,ordine) VALUES(%d,%s,%d);",sesiune_joc,id_q,(i+1));
	
	descriptor2 = sqlite3_exec(bd_global, query, NULL, 0, &zErrMsg2);
  if( descriptor2 != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg2);
      sqlite3_free(zErrMsg2);
    }
	fflush (stdout);

 }//endfor





}

