sqlite3* bd_global;
void delete_all_players()
{
    char sql[100];
  int rc_descriptor;
  char* zErrMsg=0;
  sprintf(sql," DELETE FROM SCORE;");

rc_descriptor=sqlite3_exec(bd_global,sql,NULL,0,&zErrMsg);

		if( rc_descriptor!=SQLITE_OK )
		{
			printf("SQL error \n ");
			sqlite3_free(zErrMsg);
		}
printf("s-au sters jucatorii din bd\n");
}