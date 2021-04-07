unsigned int sesiune_joc;
void insert_to_table_Login(char* lg)
{
	char *zErrMsg = NULL;
	char sqlite_query[200];
	int rc;

    sprintf(sqlite_query,"INSERT INTO Score(Name_client,punctaj, id_serie) VALUES('%s', 0, '%d');", lg,sesiune_joc);
    //printf("Suntem in insert!\n");
	
	rc = sqlite3_exec(bd_global, sqlite_query, NULL, 0, &zErrMsg);

		if( rc!=SQLITE_OK )
		{
			printf("SQL error \n ");
			sqlite3_free(zErrMsg);
		}
	printf("~Server~: Clientul s-a logat cu succes ! \n");
	printf("sesiunea : %d\n",sesiune_joc);
	fflush (stdout);

}