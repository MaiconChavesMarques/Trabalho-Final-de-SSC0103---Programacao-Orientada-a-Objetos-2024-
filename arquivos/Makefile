all: gerencia-arquivo.exe

gerencia-arquivo.exe: cabecalho.o removidos.o funcoes_fornecidas.o gerencia-arquivo.o registro.o escreveBin.o interpreta-bin.o indice.o criarIndice.o percorreCsv.o registroIndice.o inserirDado.o registroArvoreB.o cabecalhoArvoreB.o arvoreB.o main.o
	gcc registro.o cabecalho.o removidos.o gerencia-arquivo.o escreveBin.o interpreta-bin.o funcoes_fornecidas.o indice.o criarIndice.o percorreCsv.o registroIndice.o inserirDado.o registroArvoreB.o cabecalhoArvoreB.o arvoreB.o main.o -o gerencia-arquivo.exe -std=c99 -Wall

shared: cabecalho.o removidos.o funcoes_fornecidas.o gerencia-arquivo.o registro.o escreveBin.o interpreta-bin.o indice.o criarIndice.o percorreCsv.o registroIndice.o inserirDado.o registroArvoreB.o cabecalhoArvoreB.o arvoreB.o main.o
	gcc -shared -o libbiblioteca.so cabecalho.o removidos.o funcoes_fornecidas.o gerencia-arquivo.o registro.o escreveBin.o interpreta-bin.o indice.o criarIndice.o percorreCsv.o registroIndice.o inserirDado.o registroArvoreB.o cabecalhoArvoreB.o arvoreB.o main.o

removidos.o:
	gcc -c removidos.c -o removidos.o -fPIC

funcoes_fornecidas.o:
	gcc -c funcoes_fornecidas.c -o funcoes_fornecidas.o -fPIC

gerencia-arquivo.o:
	gcc -c gerencia-arquivo.c -o gerencia-arquivo.o -fPIC

registro.o:
	gcc -c registro.c -o registro.o -fPIC

escreveBin.o:
	gcc -c escreveBin.c -o escreveBin.o -fPIC

interpreta-bin.o:
	gcc -c interpreta-bin.c -o interpreta-bin.o -fPIC

cabecalho.o:
	gcc -c cabecalho.c -o cabecalho.o -fPIC

indice.o:
	gcc -c indice.c -o indice.o -fPIC

criarIndice.o:
	gcc -c criarIndice.c -o criarIndice.o -fPIC

percorreCsv.o:
	gcc -c percorreCsv.c -o percorreCsv.o -fPIC

registroIndice.o:
	gcc -c registroIndice.c -o registroIndice.o -fPIC

inserirDado.o:
	gcc -c inserirDado.c -o inserirDado.o -fPIC

registroArvoreB.o:
	gcc -c registroArvoreB.c -o registroArvoreB.o -fPIC

cabecalhoArvoreB.o:
	gcc -c cabecalhoArvoreB.c -o cabecalhoArvoreB.o -fPIC

arvoreB.o:
	gcc -c arvoreB.c -o arvoreB.o -fPIC
	  
main.o:
	gcc -c main.c -o main.o -fPIC

debug: CFLAGS += -g
debug: clean gerencia-arquivo.exe

clean:
	rm *.o gerencia-arquivo.exe libbiblioteca.so

run:
	./gerencia-arquivo.exe

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./gerencia-arquivo.exe
