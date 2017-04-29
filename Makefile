OS=LINUX
CORE = core/cadre.cpp core/game.cpp core/keyboard.cpp core/partition.cpp core/menu.cpp core/partitionMaker.cpp core/class.cpp core/score.cpp

SRCS_SDL = $(CORE) sdl2/sdlPartitionMaker.cpp sdl2/mainSdl.cpp sdl2/sdlClass.cpp sdl2/sdlMenu.cpp sdl2/sdlGame.cpp
FINAL_TARGET_SDL = starstreak
#DEFINE_SDL = -DJEU_SDL


ifeq ($(OS),Windows_NT)
	INCLUDE_DIR_SDL = 	-Iextern/SDL2_mingw/SDL2-2.0.3/include \
						-Iextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2
	LIBS_SDL = 	-Lextern \
			-Lextern/SDL2_mingw/SDL2-2.0.3/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/lib \
			-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll
else
	INCLUDE_DIR_SDL = -I/usr/local/include/SDL2 -I/usr/local/include
	LIBS_SDL = -L/usr/local/Cellar/sdl2/2.0.5/lib/ -L/usr/local/Cellar/sdl2_ttf/2.0.14/lib/  -L/usr/local/Cellar/sdl2_mixer/2.0.1/lib/ -L/usr/local/Cellar/sdl2_image/2.0.1_2/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
endif

CC					= g++
LD 					= g++
LDFLAGS  			=
CPPFLAGS 			= -Wall -ggdb -std=c++11 #-O2   # pour optimiser
OBJ_DIR 			= obj
SRC_DIR 			= src
BIN_DIR 			= bin
INCLUDE_DIR			= -Isrc -Isrc/core -Isrc/sdl2

default: make_dir $(BIN_DIR)/$(FINAL_TARGET_SDL)

make_dir:
ifeq ($(OS),Windows_NT)
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR) $(OBJ_DIR)\sdl2 $(OBJ_DIR)\core
else
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR) $(OBJ_DIR)/sdl2 $(OBJ_DIR)/core
endif

$(BIN_DIR)/$(FINAL_TARGET_SDL): $(SRCS_SDL:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIBS_SDL)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $(INCLUDE_DIR_SDL) $(INCLUDE_DIR) $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /f $(OBJ_DIR)\txt\*.o $(OBJ_DIR)\sdl2\*.o $(OBJ_DIR)\core\*.o $(BIN_DIR)\$(FINAL_TARGET_TXT).exe $(BIN_DIR)\$(FINAL_TARGET_SDL).exe
else
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(FINAL_TARGET_SDL)
endif