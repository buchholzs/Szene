vpath_src = examples source source/args source/debug source/geometry\
	source/object source/platform source/graphics source/desktop\
	source/support source/event source/draw source/pointer\
	utils/fontdump utils/modules utils/speed utils/ttfdump
vpath %.c $(vpath_src)

OBJFILES=alert.o alloc.o animate.o bar.o blit.o blitfs.o blits.o blitts.o\
	btn.o btncanc.o btnexit.o btnok.o btnpush.o btnradio.o btntogg.o\
	buffdbl.o check.o check1.o checkbox.o clip.o clipblit.o close.o\
	cursor.o decorate.o defsize.o desktop.o direct.o dragdrop.o draw.o\
	editarea.o editline.o editor.o editscrl.o emptyin.o emptyout.o\
	event.o event2.o file1.o file2.o file3.o file4.o filesel.o\
	findfirs.o focus.o font.o fontaa.o fontadd.o fontdef.o fontdef2.o\
	fontdef3.o fontdef4.o fontdef5.o fontdump.o fontpix.o frame.o\
	frame1.o frame2.o geom1.o geom2.o geomencl.o geometry.o geomjc.o\
	geomjc2.o getpix.o getpixs.o globals.o hide.o hline.o hlines.o\
	iblit.o ihline.o iload.o iload2.o iloadbmp.o iloadpcx.o image.o\
	image1.o image16.o image24.o image32.o image4.o image8.o irect.o\
	ivline.o list.o listarea.o listdef.o menu.o menupd.o mouse.o move.o\
	mover.o object.o objexist.o objins.o objnew.o objrem.o objsort.o\
	objzor2.o objzord.o panel.o pixel.o pixelcl.o pixelcl2.o pixelclt.o\
	pixels.o pixelt.o pixelts.o platform.o platin.o platout.o platsys.o\
	pointer.o pointhld.o pointmve.o pop.o posmch.o posmcw.o posmove.o\
	posmx.o posmy.o possize.o queue.o radio.o radiogrp.o rect.o rects.o\
	region.o region2.o region3.o region4.o relation.o resize.o\
	resize2.o root.o scroll.o scroll2.o slider.o sliderh.o sliderv.o\
	statict.o statict2.o statict3.o text.o text1.o text2.o text3.o\
	text4.o text5.o text6.o textare2.o textare3.o textare4.o textarea.o\
	textarsc.o textlin3.o textlin4.o textline.o vline.o vlines.o\
	window.o window2.o
   
CFLAGS = -ggdb\
	-DNDEBUG -DGRX_BUG256C -DGRXMain=main\

EXAMPLES = examples/ex0.exe examples/ex1.exe examples/ex2.exe\
	examples/ex3.exe examples/ex4.exe examples/ex5.exe examples/ex6.exe\
	examples/ex7.exe examples/ex8.exe examples/ex9.exe examples/ex10.exe\
	examples/ex11.exe examples/ex12.exe examples/ex14.exe\
	examples/ex15.exe examples/ex16.exe examples/ex17.exe examples/ex18.exe\
	examples/ex19.exe examples/ex20.exe examples/ex21.exe examples/ex22.exe\
	examples/ex23.exe examples/_ex.exe

TESTEXAMPLES = examples/_ex.exe

EXELIBS = $(addprefix -l,$(EXELIBRARIES))
INCLUDE_DIRS += include source
INCLUDES = $(addprefix -I,$(INCLUDE_DIRS))
LIBRARY_DIRS += lib
LIB_DIRS = $(addprefix -L,$(LIBRARY_DIRS))
CPPFLAGS += $(INCLUDES) -DGRX_NATIVE_POINTER

ifdef DEBUG
CPPFLAGS += -ggdb
else
CPPFLAGS += -O3
endif

all : examples 

lib : $(LIBNAME) $(OBJFILES)

examples : lib $(EXAMPLES)

test : lib $(TESTEXAMPLES)

$(LIBNAME) : $(OBJFILES)
	ar rs $@ $^

%.exe : %.o
	gcc $(LIB_DIRS) -ggdb -o $@ $< $(EXELIBS) $(EXEEXTRA)

indent :
	find . -name "*.c" -type f -exec indent -kr -l135 -ts3 -lp -bad -fca -npsl -sob -nhnl -bap {} \;
	find . -name "*.h" -type f -exec indent -kr -l135 -ts3 -lp -bad -fca -npsl -sob -nhnl -bap {} \;
	find . -name "*.c~" -type f -exec rm -f {} \;
	find . -name "*.h~" -type f -exec rm -f {} \;
	
execute :
	find . -name "*.sh" -type f -exec chmod a+x {} \;

include depend.inc



