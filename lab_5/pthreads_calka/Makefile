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

calka: calka.o
	$(LOADER) $(OPT) calka.o -o calka $(LIB)

calka.o: calka.c
	$(CCOMP) -c $(OPT) calka.c $(INC)

clean:
	rm -f *.o
