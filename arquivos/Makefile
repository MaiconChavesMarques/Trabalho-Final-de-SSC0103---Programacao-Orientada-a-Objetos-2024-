all: help.o leitura_escrita.o leitura_impressao.o ordenacao_binaria.o main.o
	gcc help.o leitura_escrita.o leitura_impressao.o ordenacao_binaria.o main.o -o final -std=c99 -Wall

help.o: help.c
	gcc -c help.c -o help.o -fPIC

leitura_escrita.o: leitura_escrita.c
	gcc -c leitura_escrita.c -o leitura_escrita.o -fPIC

leitura_impressao.o: busca_impressao.c
	gcc -c busca_impressao.c -o leitura_impressao.o -fPIC

ordenacao_binaria.o: ordenacao_binaria.c
	gcc -c ordenacao_binaria.c -o ordenacao_binaria.o -fPIC

main.o: main.c
	gcc -c main.c -o main.o -fPIC

shared: help.o leitura_escrita.o leitura_impressao.o ordenacao_binaria.o main.o
	gcc -shared -o libbiblioteca.so -fPIC help.o leitura_escrita.o leitura_impressao.o ordenacao_binaria.o main.o

clean:
	rm *.o final libbiblioteca.so

run:
	./final
