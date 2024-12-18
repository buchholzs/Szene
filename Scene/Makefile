#
# Szene makefile for DJGPP version (GNU-make)
#
vpath_src = src
vpath %.cpp $(vpath_src)
vpath %.h $(vpath_src)

LIBOBJ=	sc_tokens.o Scene.o Controller.o SceneDesktop.o MoveMode.o \
	WalkMode.o FlyMode.o Hud.o Command.o dbgprint.o \
	Sequence.o SetMat.o TargetCommand.o Pause.o Rotator.o Mover.o XScreen_x11.o

INCLUDE_DIRS += src ../contrib/grx243/include ../depui/include ../expat/lib ../plush/src
LIBRARY_DIRS += ../contrib/grx243/lib/dj2 ../depui/lib ../expat/.libs ../plush

INCLUDES = $(addprefix -I,$(INCLUDE_DIRS))
LIB_DIRS = $(addprefix -L,$(LIBRARY_DIRS))

CC = gxx
CPPFLAGS += $(INCLUDES)
ifdef DEBUG
CPPFLAGS += -ggdb -DDEBUG
else
CPPFLAGS += -O3
endif

LDLIBS = $(LIB_DIRS) $(EXELIBS)

all: lib

lib: libscene.a $(LIBOBJ)

libscene.a: $(LIBOBJ)
	$(AR) rs $@ $^

clean:
	rm -f *.a *.o


# Dependencies


Scene.o: Scene.cpp Scene.h

Command.o: Command.cpp \
	Command.h

Controller.o: Controller.cpp \
	Controller.h \
	MoveMode.h Scene.h sc_tokens.h

Desktop.o: Desktop.cpp \
	Controller.h MoveMode.h \
	Scene.h sc_tokens.h WalkMode.h MoveMode.h FlyMode.h \
	MoveMode.h Hud.h HudRefreshCmd.h Command.h

FlyMode.o: FlyMode.cpp FlyMode.h \
	MoveMode.h Scene.h sc_tokens.h

Hud.o: Hud.cpp Hud.h

HudRefreshCmd.o: HudRefreshCmd.cpp HudRefreshCmd.h \
	Command.h Hud.h

MoveMode.o: MoveMode.cpp MoveMode.h

sc_tokens.o: sc_tokens.cpp sc_tokens.h

Scene.o: Scene.cpp Scene.h sc_tokens.h \
	Command.h

WalkMode.o: WalkMode.cpp WalkMode.h \
	MoveMode.h Scene.h sc_tokens.h

XScreen_x11.o: XScreen_x11.cpp XScreen.h