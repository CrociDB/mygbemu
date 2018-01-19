PROJ=mygbemu

CC=gcc
CFLAGS=-I.

DEPS = main.h
OBJ = main.o 

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROJ): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f *.o
