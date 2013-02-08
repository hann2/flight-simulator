
COMPILER = c99
COMPILER_OPTS = -c -g -Wall -Werror
LINKER = c99
LINKER_OPTS = -lpng -lGL -lGLU -lglut

all : flight

flight.o : flight.c flight.h
	$(COMPILER) $(COMPILER_OPTS) flight.c

flight : flight.o
	$(LINKER) flight.o $(LINKER_OPTS) -o flight

clean :
	-rm -f *.o flight