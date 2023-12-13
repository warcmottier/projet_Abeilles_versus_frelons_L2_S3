CC = gcc
CFLAGS =-std=c17 -pedantic -Wall
LDFLAGS = -lMLV
OBJ = fichier.o game.o abeille.o frelon.o graph.o liste.o main.o
EXE = AVSF
REG = src/

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	
main.o: $(REG)main.c $(REG)game.h

abeille.o: $(REG)abeille.c $(REG)abeille.h $(REG)liste.h

frelon.o: $(REG)frelon.c $(REG)frelon.h $(REG)liste.h

liste.o: $(REG)liste.c $(REG)liste.h

graph.o: $(REG)graph.c $(REG)graph.h $(REG)liste.h

fichier.o: $(REG)fichier.c $(REG)fichier.h $(REG)abeille.h $(REG)frelon.h

game.o: $(REG)game.c $(REG)game.h $(REG)abeille.h $(REG)frelon.h $(REG)graph.h $(REG)fichier.h

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
