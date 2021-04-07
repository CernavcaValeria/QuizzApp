char buf_for_question[300];
unsigned int sesiune_joc;
char extract_from_bd(int j)
{
 char *zErrMsg = NULL;
 char query_extract[300];
 sqlite3_stmt* question;

 char column_of_question[200];
 char column_of_correct_answer;

bzero (buf_for_question, strlen(buf_for_question));


 sprintf(query_extract,"SELECT quest.Q, quest.Var_1, quest.Var_2, quest.Var_3, quest.Var_4 ,quest.correct FROM Question quest JOIN Intermediate inter on quest.id_q=inter.id_q WHERE inter.id_serie=%d and inter.ordine=%d",sesiune_joc,(j+1));
 printf("________________________\n");

int question_descriptor=sqlite3_prepare_v2(bd_global,query_extract, -1,&question,0 );

   if(question_descriptor!=SQLITE_OK)
   {
      fprintf(stderr,"Eroare la extragerea intrebarii din BD : %s \n",sqlite3_errmsg(bd_global));
   }
   

 question_descriptor=sqlite3_step(question);

   
  if( question_descriptor==SQLITE_ROW)
  {
     bzero (buf_for_question, strlen(buf_for_question));
     for(int k=0; k<6; k++)
      {
       if(k<5)
       {
        sprintf(column_of_question, "%s\n",sqlite3_column_text(question, k));
        strcat(buf_for_question,column_of_question);
       }
       else if(k==5)
       {
          column_of_correct_answer=sqlite3_column_text(question, k)[0];  
       }
      }
   
  }

   sqlite3_finalize(question);
   return column_of_correct_answer;

}