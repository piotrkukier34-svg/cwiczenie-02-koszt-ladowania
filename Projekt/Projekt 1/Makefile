CC = gcc
CFLAGS = -std=c90 -Wall -Wextra -pedantic -g

macierze.exe: main.o matrix.o matrix_io.o
	$(CC) $(CFLAGS) -o $@ main.o matrix.o matrix_io.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

main.o: main.c matrix.h matrix_io.h
matrix.o: matrix.c matrix.h
matrix_io.o: matrix_io.c matrix_io.h

clean:
	del /f /q *.o macierze.exe 2>nul || exit 0

test: macierze.exe
	.\macierze.exe