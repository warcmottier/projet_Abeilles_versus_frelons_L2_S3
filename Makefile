CC = gcc
CFLAGS =-std=c17 -pedantic -Wall
LDFLAGS = -lMLV
OBJ = fichier.o game.o unite.o graph.o liste.o main.o
EXE = AVSF
REG = src/

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	
main.o: $(REG)main.c $(REG)game.h

unite.o: $(REG)unite.c $(REG)unite.h $(REG)liste.h

liste.o: $(REG)liste.c $(REG)liste.h

graph.o: $(REG)graph.c $(REG)graph.h $(REG)liste.h

fichier.o: $(REG)fichier.c $(REG)fichier.h $(REG)unite.h

game.o: $(REG)game.c $(REG)game.h $(REG)unite.h $(REG)graph.h $(REG)fichier.h

%.o: $(REG)%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXE)

install: $(EXE)
	mkdir bin
	mv $(EXE) bin/$(EXE)
	make mrproper

uninstall: mrproper
	rm -f bin/$(EXE)
	rm -rf bin
