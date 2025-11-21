CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2

OBJS = main.o utils.o cadastro.o lista.o ataque.o missoes.o memoria.o

all: war

war: $(OBJS)
	$(CC) $(CFLAGS) -o war $(OBJS)

main.o: main.c territorio.h utils.h cadastro.h lista.h ataque.h missoes.h memoria.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

cadastro.o: cadastro.c cadastro.h utils.h territorio.h
	$(CC) $(CFLAGS) -c cadastro.c

lista.o: lista.c lista.h territorio.h
	$(CC) $(CFLAGS) -c lista.c

ataque.o: ataque.c ataque.h territorio.h
	$(CC) $(CFLAGS) -c ataque.c

missoes.o: missoes.c missoes.h territorio.h
	$(CC) $(CFLAGS) -c missoes.c

memoria.o: memoria.c memoria.h territorio.h
	$(CC) $(CFLAGS) -c memoria.c

clean:
	rm -f *.o war
