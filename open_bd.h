sqlite3* bd_global;
void open_BD()
{
 int open_bd;
 open_bd = sqlite3_open("QuizzGame.db",&bd_global);

   if(open_bd) 
   {
      fprintf(stderr, "Nu se poate deschide baza de date: %s\n", sqlite3_errmsg(bd_global));
      //return(0);
   }
   else
   {
      fprintf(stderr, "Baza de data s-a deschis cu succes\n");
   }	 
}

