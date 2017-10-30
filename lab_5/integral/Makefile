# C compiler
CCOMP = gcc

# Consolidation
LOADER = gcc

# Optimalization options

# Debug mode
#OPT = -g -DDEBUG
# Optimalized mode for time measuring
OPT = -O3

#Time measuring
INC = -I../pomiar_czasu

LIB = -L../pomiar_czasu -lpomiar_czasu -lm -lpthread


# Dependencies and commands

program: program.o
	$(LOADER) $(OPT) program.o -o program $(LIB)

program.o: program.c
	$(CCOMP) -c $(OPT) program.c $(INC)

clean:
	rm -f *.o
