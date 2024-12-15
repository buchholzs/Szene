include ../mrules.inc

all: Matedit

Matedit : matedit.o $(PARENTLIBS)
	$(LINK.o) $< $(LDLIBS) -o $@

clean:
	rm -f Matedit *.o

# Dependencies
