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
	cmd /c rmdir /s/q redist
	cmd /c md redist
	cmd /c copy MatEdit2\matedit2.exe redist
	cmd /c copy PlushPlayer\plushplr.exe redist
	cmd /c copy MatEdit2\standard.scx redist
	cmd /c copy MatEdit2\Release\matedit2.exe redist\matedit2_w32.exe
	cmd /c copy PlushPlayer\Release\plushplr.exe redist\plushplr_w32.exe
	cmd /c copy Archiv\CWSDPMI.EXE redist
	cmd /c copy Readme.txt redist
	cmd /c copy changelog.txt redist
	cmd /c copy Expat-1.95.2\Libs\expat.dll redist
	cmd /c mkdir redist\scenes
	cmd /c copy "PlushPlayer\scenes\*.scx" redist\scenes
	cmd /c copy "PlushPlayer\scenes\*.pcx" redist\scenes
	cmd /c copy "PlushPlayer\scenes\*.JAW" redist\scenes
	cmd /c mkdir redist\scenes\maps
	cmd /c copy "PlushPlayer\scenes\Maps\*.pcx" redist\scenes\maps

# Dependencies

exe: $(EXE) lib

lib: expat grx plush depui scene