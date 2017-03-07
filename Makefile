CXXFLAGS=-Wall -ggdb

LIB = -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDE = -I/usr/include/SDL2 -Isrc

#dit au makefile de chercher les .cpp dans le dossier dir
vpath %.cpp src

OBJET=obj/jeu.o obj/partie.o obj/partition.o obj/score.h

all:  make_dir guitarZero

make_dir :
	test -d obj || mkdir -p obj data bin

jeu: $(OBJET) obj/mainJeu.o
	g++ -o bin/$@ $^ $(LIB)

partie: $(OBJET) obj/mainPartie.o
	g++ -o bin/$@ $^ $(LIB)

partition: $(OBJET) obj/mainPartition.o
	g++ -o bin/$@ $^ $(LIB)

score: $(OBJET) obj/mainScore.o
	g++ -o bin/$@ $^ $(LIB)

obj/%.o : %.cpp
	g++ -c $(CXXFLAGS) $(INCLUDE) $^ -o $@ 

clean:
	rm -f obj/*.o

superclean: clean
	rm -f bin/*