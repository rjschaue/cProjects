CC = gcc
CFLAGS = -Wall -std=c99

hangman: hangman.o display.o wordlist.o

hangman.o: display.h wordlist.h
display.o: display.h
wordlist.o: wordlist.h

clean:
	rm -f main.o display.o wordlist.o
