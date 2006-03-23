install : lib
	cp -rf include/* /usr/local/include
	cp -f lib/*.a /usr/local/lib

uninstall : 
	-rm -f /usr/local/include/depui
	-rm -f /usr/local/include/depui.htm
	-rm -f /usr/local/lib/lipdepui.a

clean :
	-rm -f *.o
	-rm -f *.exe
	-rm -f lib/*.a
	-rm -f examples/*.o 
	-rm -f examples/*.exe
	-rm -f examples/*.gdt
	-rm -f examples/*.dat
	-rm -f examples/*.mak
	-rm -f -r *.c~
	-rm -f -r *.h~

tgz : clean execute
	-tar -cv * >depui.tar
	-gzip -c <depui.tar >depui.tgz
	-rm -f depui.tar




