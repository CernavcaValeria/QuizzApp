void insert_quest_from_cl(char* question)
{char *zErrMsg = NULL;
	char query[300];
	int rc;

  sprintf(query,"INSERT INTO Question(id_q,Q,Var_1,Var_2,Var_3,Var_4,correct) VALUES(%s);",question);
  printf("Suntem in insert!\n");
	
	rc = sqlite3_exec(bd_global, query, NULL, 0, &zErrMsg);
  if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
	fflush (stdout);
}