FLAG = -std=c11 -Wall -Wextra -Werror -Wpedantic 
CC = clang
VAR_C = main.c play_screen.c menue.c time_functions.c files_functions.c string_functions.c
VAR_O = main.o play_screen.o menue.o time_functions.o files_functions.o string_functions.o
LN = -lncurses

all: install clean

uninstall: rm_obj clean 
	
reinstall: rm_obj clean install
	
clean:
	rm -rf *.c 
	rm -rf *.h
	rm -rf *.o
	
install: 
	cp src/*.c .
	cp inc/*.h .
	$(CC) $(FLAG) -c $(VAR_C)
	$(CC) $(FLAG) $(VAR_O) -o endgame $(LN) 
	
rm_obj:
	rm -drf obj


	
	

