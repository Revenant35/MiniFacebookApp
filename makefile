makefile: main.c hash.c friends.c users.c
	gcc -o run main.c hash.c friends.c users.c -I