vpath_src = src
vpath %.cpp $(vpath_src)

LIB=expat/.libs/libexpat.a plush/libplush.a contrib/grx248/lib/unix/libgrx20X.a depui/lib/libdepui.a Scene/libscene.a

PARENTLIBS = $(addprefix ../,$(LIB))

EXELIBRARIES = scene depui grx20X plush expat X11 m stdc++

INCLUDE_DIRS += ../Scene/src ../contrib/grx248/include ../depui/include ../expat/lib ../plush/src
LIBRARY_DIRS += ../Scene ../contrib/grx248/lib/unix ../depui/lib ../expat/.libs ../plush

EXELIBS = $(addprefix -l,$(EXELIBRARIES))
INCLUDES = $(addprefix -I,$(INCLUDE_DIRS))
LIB_DIRS = $(addprefix -L,$(LIBRARY_DIRS))

CC = g++
CPPFLAGS += $(INCLUDES) -DGRX_NATIVE_POINTER
ifdef DEBUG
CPPFLAGS += -ggdb
else
CPPFLAGS += -O3
endif

LDLIBS = $(LIB_DIRS) $(EXELIBS)


 