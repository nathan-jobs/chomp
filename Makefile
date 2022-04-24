CFLAGS = -ansi -pedantic -Wall -Wfatal-errors
LDFLAGS = -lMLV
CC = gcc

OBJS = main.o affichage.o jeu.o creation.o 
	
chomp : $(OBJS) 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 
	

	
clean : 
	rm -f *.o
	
mrproper : clean
	rm -f $@

