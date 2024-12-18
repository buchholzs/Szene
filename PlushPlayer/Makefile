include ../mrules.inc

all: PlushPlayer

PlushPlayer: PlushPlayer.o $(PARENTLIBS)
	$(LINK.o) $< $(LDLIBS) -o $@

clean:
	rm -f PlushPlayer *.o

# Dependencies
