PROJ=mygbemu
DIR=emulator
SDL = -lSDL2main -lSDL2

CC=gcc
CFLAGS=-I/usr/include/SDL2 -I$(DIR)


DEPS = log.h sys.h cartridge.h mmu.h cpu.h util.h debug.h ppu.h canvas.h
OBJ = $(DIR)/main.o $(DIR)/cpu.o $(DIR)/cartridge.o $(DIR)/sys.o $(DIR)/mmu.o\
      $(DIR)/log.o $(DIR)/util.o $(DIR)/debug.o $(DIR)/ppu.o $(DIR)/canvas.o

$(DIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

$(PROJ): $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) $(SDL)
	
all: $(PROJ)

.PHONY: clean
clean: 
	rm -f $(DIR)/*.o $(PROJ)
