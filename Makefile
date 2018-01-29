PROJ=mygbemu
DIR=emulator

CC=gcc
CFLAGS=-I$(DIR)


DEPS = log.h sys.h cartridge.h mmu.h cpu.h util.h debug.h
OBJ = $(DIR)/main.o $(DIR)/log.o $(DIR)/cartridge.o $(DIR)/sys.o $(DIR)/mmu.o $(DIR)/cpu.o $(DIR)/util.o $(DIR)/debug.o

$(DIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

$(PROJ): $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f $(DIR)/*.o $(PROJ)
