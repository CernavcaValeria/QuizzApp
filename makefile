all: 
	gcc server_pr.c -o cs.o -lpthread -lm -lsqlite3
     	gcc client_pr.c -o cc.o 

clean:
	rm -f *~cc.o cs.o


