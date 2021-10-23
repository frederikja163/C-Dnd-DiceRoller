CC=gcc
CLFAGS=-I$(SRC)

roller: roller.o clean
	$(CC) roller.c -o $@

roll: roll.o clean
	$(CC) roll.c -o $@

clean:
	del -rf *.o