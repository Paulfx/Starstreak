CXXFLAGS=-Wall -ggdb


#UNIX -> OSX + LINUX 

LIB = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDE = -I/usr/local/include/SDL2 -I/usr/local/include -Isrc

#dit au makefile de chercher les .cpp dans le dossier dir
#vpath %.cpp src

OBJET=obj/menu.o obj/game.o obj/partition.o obj/score.o obj/keyboard.o  

all:  make_dir starStreak

make_dir :
	test -d obj || mkdir -p obj bin

game: $(OBJET) obj/mainGame.o
	g++ -o bin/$@ $^ -std=c++11

menu: $(OBJET) obj/mainTxt.o obj/winTxt.o obj/txtGame.o
	g++ -o bin/$@ $^ -Itxt -std=c++11 

partition: obj/partition.o obj/mainPartition.o
	g++ -o bin/$@ $^ -std=c++11

score: $(OBJET) obj/mainScore.o obj/keyboard.o
	g++ -o bin/$@ $^  -std=c++11

test : obj/mainTest.o obj/partition.o obj/keyboard
	g++ -o bin/$@ $^ -std=c++11

SDL: $(OBJET) obj/sdlGame.o obj/mainSDL.o # ////
	g++ -o bin/$@ $^ -std=c++11	$(INCLUDE) $(LIB)


obj/%.o : src/%.cpp
	g++ -c $(CXXFLAGS) $^ -o $@ -std=c++11 $(INCLUDE)

clean:
	rm -f obj/*.o

superclean: clean
	rm -f bin/*
