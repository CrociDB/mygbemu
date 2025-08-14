SRC = hello-world.asm
OBJ = hello-world.o
ROM = hello-world.gb

all: $(ROM)

$(OBJ): $(SRC)
	rgbasm -o $(OBJ) $(SRC)

$(ROM): $(OBJ)
	rgblink -o $(ROM) $(OBJ)
	rgbfix -v -p 0 $(ROM)

clean:
	rm -f $(OBJ) $(ROM)
