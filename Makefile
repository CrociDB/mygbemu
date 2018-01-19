PROJ=mygbemu

CC=gcc
CFLAGS=-I.

DEPS = emulator/main.h
OBJ = emulator/main.o 

emulator/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROJ): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f *.o $(PROJ)
