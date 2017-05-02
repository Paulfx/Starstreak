CORE = core/cadre.cpp core/game.cpp core/keyboard.cpp core/partition.cpp core/menu.cpp core/partitionMaker.cpp core/class.cpp core/score.cpp

SRCS_SDL = $(CORE) sdl2/sdlPartitionMaker.cpp sdl2/mainSdl.cpp sdl2/sdlClass.cpp sdl2/sdlMenu.cpp sdl2/sdlGame.cpp
FINAL_TARGET_SDL = starstreak

SRCS_TXT = $(CORE) txt/txtGame.cpp txt/winTxt.cpp txt/mainTxt.cpp
FINAL_TARGET_TXT = starstreakTxt

	INCLUDE_DIR_SDL = -I/usr/local/include/SDL2 -I/usr/local/include
	LIBS_SDL = -L/usr/local/Cellar/sdl2/2.0.5/lib/ -L/usr/local/Cellar/sdl2_ttf/2.0.14/lib/  -L/usr/local/Cellar/sdl2_mixer/2.0.1/lib/ -L/usr/local/Cellar/sdl2_image/2.0.1_2/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

CC					= g++
LD 					= g++
LDFLAGS  			=
CPPFLAGS 			= -Wall -ggdb -std=c++11 #-O2   # pour optimiser
OBJ_DIR 			= obj
SRC_DIR 			= src
BIN_DIR 			= bin
INCLUDE_DIR			= -Isrc -Isrc/core -Isrc/sdl2

default: make_dir $(BIN_DIR)/$(FINAL_TARGET_SDL) $(BIN_DIR)/$(FINAL_TARGET_TXT)

make_dir:
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR) $(OBJ_DIR)/sdl2 $(OBJ_DIR)/core $(OBJ_DIR)/txt


$(BIN_DIR)/$(FINAL_TARGET_SDL): $(SRCS_SDL:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIBS_SDL)

$(BIN_DIR)/$(FINAL_TARGET_TXT): $(SRCS_TXT:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $(INCLUDE_DIR_SDL) $(INCLUDE_DIR) $< -o $@


archive:
	tar czvf rendu.tar.gz \
		--exclude "*.tar.gz" \
		--exclude "*.o" \
		--exclude "*.d" \
		*

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(FINAL_TARGET_SDL)