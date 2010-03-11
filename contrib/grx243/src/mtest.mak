OBJDIR = source/debug

VPATH = $(OBJDIR)

%.o : %.c
	$(COMPILE.c) $< -o $(OBJDIR)/$@

all: foo

foo: alloc.o
	$(LINK.o) $^ $(LDLIBS) -o $(OBJDIR)/$@
