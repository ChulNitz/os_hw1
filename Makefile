SRC_DIR := src
OBJ_DIR := obj

EXE := hw1shell

SRC := $(wildcard $(SRC_DIR)/*.c)

all: $(SRC)
	gcc $(SRC) -g -o $(EXE) -I include/

clean:
	rm $(EXE)

