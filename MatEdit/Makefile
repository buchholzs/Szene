include ../mrules.inc

all: MatEdit

MatEdit : matedit.o $(PARENTLIBS)
	$(LINK.o) $< $(LDLIBS) -o $@

clean:
	rm -f MatEdit *.o

# Dependencies
