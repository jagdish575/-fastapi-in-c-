CC = gcc
CFLAGS = -Wall

all: server

server: main.o server.o router.o
	$(CC) $(CFLAGS) -o server main.o server.o router.o

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

server.o: src/server.c
	$(CC) $(CFLAGS) -c src/server.c

router.o: src/router.c
	$(CC) $(CFLAGS) -c src/router.c

clean:
	rm -f *.o server
