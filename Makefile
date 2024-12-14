#
# Szene makefile for DJGPP version (GNU-make)
#

EXE=PlushPlayer/PlushPlayer MatEdit/Matedit

LIB=expat/libexpat.a plush/libplush.a contrib/grx248/lib/dj2/libgrx20.a depui/lib/libdepui.a Scene/libscene.a

# Rules
all: lib exe

expat/libexpat.a:
	$(MAKE) -C expat

contrib/grx248/lib/dj2/libgrx20.a:
	$(MAKE) -C contrib/grx248 -f makefile.x11 libs

plush/libplush.a:
	$(MAKE) -C plush/src -f MAKEFILE	

depui/lib/libdepui.a:
	$(MAKE) -C depui -f MAKEFILE lib

Scene/libscene.a:
	$(MAKE) -C Scene -f MAKEFILE all

MatEdit/Matedit: $(LIB)
	$(MAKE) -C MatEdit -f MAKEFILE

PlushPlayer/PlushPlayer: $(LIB)
	$(MAKE) -C PlushPlayer -f MAKEFILE

clean:
	$(MAKE) -C Expat-1.95.2/Source/lib -f MAKEFILE clean
	$(MAKE) -C plush/src -f MAKEFILE clean	
	$(MAKE) -C contrib/grx248 -f makefile.dj2 clean
	del contrib\grx248\lib\dj2\libgrx20.a
	$(MAKE) -C depui -f MAKEFILE clean
	$(MAKE) -C Scene -f MAKEFILE clean
	$(MAKE) -C MatEdit -f MAKEFILE clean
	$(MAKE) -C PlushPlayer -f MAKEFILE clean

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

exe: $(EXE)

lib: $(LIB)
