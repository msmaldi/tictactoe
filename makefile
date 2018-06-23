CC=gcc
SRCS=src/main.c src/tictactoe.c src/minimax.c
PKG_CONFIG=pkg-config --cflags --libs gtk+-3.0
BIN=tictactoe
CFLAGS=-O3

run: tictactoe
	./$(BIN)

all: tictactoe tictactoe-shared

tictactoe: main.o tictactoe.o minimax.o
	$(CC) $^ `$(PKG_CONFIG)` $(CFLAGS) -o $@ -O3

tictactoe-shared: main.o libtictactoe.so
	$(CC) $^ `$(PKG_CONFIG)` $(CFLAGS) -o $@ -O3 -L /home/msmaldi/Projects/c/tictactoe -ltictactoe

libtictactoe.so: src/tictactoe.c src/minimax.c
	$(CC) -O3 -fPIC -shared -o $@ $^ `pkg-config --cflags --libs glib-2.0`

main.o: src/main.c
	$(CC) -c -o $@ $^ `$(PKG_CONFIG)` -O3

tictactoe.o: src/tictactoe.c
	$(CC) -c -o $@ $^ `pkg-config --cflags --libs glib-2.0` -O3

minimax.o:  src/minimax.c
	$(CC) -c -o $@ $^ `pkg-config --cflags --libs glib-2.0` -O3

clean: 
	rm -f tictactoe tictactoe-shared *.o *.so *.a