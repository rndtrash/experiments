CC=gcc
override CFLAGS+=
LD=gcc
override LDFLAGS+=

.PHONY: all clean

all: parser

parser: parser.o
	$(LD) parser.o $(LDFLAGS) -o bin/parser

%.o: $(CC) %.c $(FLAGS) -o %.o

clean:
	rm -f *.o
	find bin/ ! -name '.gitkeep' -type f -exec rm -f {} +
