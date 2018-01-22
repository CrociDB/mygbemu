PROJ=mygbemu
DIR=emulator

CC=gcc
CFLAGS=-I$(DIR)


DEPS = sys.h cartridge.h mmu.h
OBJ = $(DIR)/main.o $(DIR)/cartridge.o $(DIR)/sys.o $(DIR)/mmu.o

$(DIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

$(PROJ): $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f $(DIR)/*.o $(PROJ)
