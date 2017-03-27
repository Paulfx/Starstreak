CXXFLAGS=-Wall -ggdb

#LIB = -lSDL2 -lSDL2_ttf -lSDL2_image
#INCLUDE = -I/usr/include/SDL2 -Isrc

#dit au makefile de chercher les .cpp dans le dossier dir
vpath %.cpp src

OBJET=obj/menu.o obj/game.o obj/partition.o obj/score.o obj/keyboard.o

all:  make_dir straStreak

make_dir :
	test -d obj || mkdir -p obj bin

game: $(OBJET) obj/mainGame.o
	g++ -o bin/$@ $^ 

menu: $(OBJET) obj/mainMenu.o
	g++ -o bin/$@ $^ 

partition: obj/partition.o obj/mainPartition.o
	g++ -o bin/$@ $^ 

score: $(OBJET) obj/mainScore.o
	g++ -o bin/$@ $^ 


obj/%.o : %.cpp
	g++ -c $(CXXFLAGS) $^ -o $@ 

clean:
	rm -f obj/*.o

superclean: clean
	rm -f bin/*
