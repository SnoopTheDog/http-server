linux:
	clang src/main.c -o main -Iinclude -L/usr/lib/ -lmicrohttpd

windows: 
	gcc src/main.c -o main.exe -Iinclude -Llib -lmicrohttpd