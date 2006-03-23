install : lib
	copy lib\*.a $(DJDIR)\lib
	copy -R include $(DJDIR)

uninstall :
	-del $(DJDIR)\lib\libdepui.a
	-del $(DJDIR)\include\depui.h
	-deltree /Y $(DJDIR)\include\depui

clean :
	-del *.o
	-del *.dsk
	-del *.obj
	-del *.exe
	-del lib\*.a
	-del examples\*.o 
	-del examples\*.obj
	-del examples\*.exe
	-del examples\*.gdt
	-del examples\*.dat
	-del examples\*.mak

zip : clean
	-pkzip -r -p -ex depui




