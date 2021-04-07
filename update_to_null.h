void update_to_null(char* login){
    char sql[100];
  int rc_descriptor;
  char* zErrMsg=0;
  sprintf(sql,"UPDATE Score set punctaj=0 WHERE Name_client='%s' ; ",login);

rc_descriptor=sqlite3_exec(bd_global,sql,NULL,0,&zErrMsg);

		if( rc_descriptor!=SQLITE_OK )
		{
			printf("SQL error \n ");
			sqlite3_free(zErrMsg);
		}
}