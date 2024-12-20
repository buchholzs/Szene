#
# Szene makefile for GNU-make
#

.PHONY: expat grx plush depui scene

EXE=PlushPlayer/PlushPlayer MatEdit/Matedit

ifdef DEBUG
DEBUGFLAG = DEBUG=1
endif

# Rules
all: lib exe

expat:
	$(MAKE) $(DEBUGFLAG) -C expat

grx:
	$(MAKE) $(DEBUGFLAG) -C contrib/grx248 -f makefile.x11 libs

plush:
	$(MAKE) $(DEBUGFLAG) -C plush/src

depui:
	$(MAKE) $(DEBUGFLAG) -C depui lib

scene:
	$(MAKE) $(DEBUGFLAG) -C Scene all

MatEdit/Matedit: lib
	$(MAKE) $(DEBUGFLAG) -C MatEdit

PlushPlayer/PlushPlayer: lib
	$(MAKE) $(DEBUGFLAG) -C PlushPlayer

clean:
	$(MAKE) $(DEBUGFLAG) -C expat clean
	$(MAKE) $(DEBUGFLAG) -C plush/src clean	
	$(MAKE) $(DEBUGFLAG) -C contrib/grx248 -f makefile.x11 clean
	$(MAKE) $(DEBUGFLAG) -C depui clean
	$(MAKE) $(DEBUGFLAG) -C Scene clean
	$(MAKE) $(DEBUGFLAG) -C MatEdit clean
	$(MAKE) $(DEBUGFLAG) -C PlushPlayer clean

install:	
	cp PlushPlayer/PlushPlayer PlushPlayer-MatEdit
	cp MatEdit/MatEdit PlushPlayer-MatEdit

# Dependencies

exe: $(EXE) lib

lib: expat grx plush depui scene