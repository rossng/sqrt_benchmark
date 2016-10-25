# Makefile

EXE=sqrt_benchmark

CC=icc
CFLAGS= -std=c99 -Wall -O0
LIBS = -lm
EXTRAFLAGS= -debug full

all: $(EXE)

$(EXE): $(EXE).c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) $^ $(LIBS) -o $@

.PHONY: all check clean

clean:
	rm -f $(EXE)

