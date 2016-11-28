help:
	@echo "make help"
	@echo "make all"


ADT_AVL.o: ADT_AVL.c
	g++ -c ADT_AVL.c

main.o: main.c
	g++ -c main.c

all: ADT_AVL.o main.o
	g++ -o AVL.exe main.o ADT_AVL.o

run: all
	AVL.exe	

clean: 
	del *.o

cleanup: clean
	del *.exe

	

