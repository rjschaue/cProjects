CC = gcc
CFLAGS = -Wall -std=c99

hangman: hangman.o display.o display.h wordlist.o wordlist.h

hangman.o: display.h wordlist.h
display.o: display.h
wordlist.o: wordlist.h

clean:
	rm -f main.o display.o wordlist.o
	rm -f hangman
	rm -f output.txt stdout.txt
