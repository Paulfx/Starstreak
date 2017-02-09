EXEC_NAME = exec.out
OBJ_FILES = main.o Image.o Pixel.o
CC = g++ 
CFLAGS = -Wall -ggdb
INCLUDES = -I/usr/include
LIBS = -L/usr/lib -lm

all: $(EXEC_NAME) 

$(EXEC_NAME): $(OBJ_FILES) 
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS) 

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $< 
clean: 
	rm $(OBJ_FILES)
