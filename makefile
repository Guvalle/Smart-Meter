COMP=g++
CFLAGS=-I 
DEPS = phase.h sampler.h mcp3008.h calculator.h util.h database.h
OBJ = main.o sampler.o mcp3008.o calculator.o util.o database.o
LIBS= -lwiringPi -lsqlite3 -lm -lrt

%.o: %.c $(DEPS)
	$(COMP) -cpp -o $@ $< $(CFLAGS)

meter: $(OBJ) 
	gcc -o $@ $^ $(LIBS) $(CFLAGS).

clean:
	rm -f *.o