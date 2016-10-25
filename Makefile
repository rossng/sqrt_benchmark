# Makefile

EXE=sqrt_benchmark

CC=icc
CFLAGS= -std=c99 -Wall -Ofast -no-prec-div -xsse4.2 -no-prec-sqrt
LIBS = -lm
EXTRAFLAGS= -debug full

all: $(EXE)

$(EXE): $(EXE).c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) $^ $(LIBS) -o $@

.PHONY: all check clean

clean:
	rm -f $(EXE)

