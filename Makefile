IDIR =include

ODIR=obj

SDIR=src

EXE=4th
CC=gcc
CFLAGS=-I$(IDIR)
LIBS=-lm

ENSUREBUILDDIR = $(shell test -d $(ODIR) || mkdir $(ODIR))

CFILES = $(patsubst $(SDIR)/%.c,%.c, $(wildcard $(SDIR)/*.c))

HEADERS := $(wildcard $(IDIR)/*.h)

OBJS = $(patsubst %.c,$(ODIR)/%.o,$(CFILES)) 

all: $(ENSUREBUILDDIR) $(EXE)

$(ODIR)/%.o : $(SDIR)/%.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJS)
	@echo 
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean test

test: $(EXE)
	./test.sh
clean:
	rm -f $(OBJS)
	rm -f $(EXE)
