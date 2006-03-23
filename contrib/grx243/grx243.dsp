# Microsoft Developer Studio Project File - Name="grx243" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=grx243 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "grx243.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "grx243.mak" CFG="grx243 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "grx243 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "grx243 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "grx243 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "include" /I "src" /I "src/include" /I "addons\print" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "grx243 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "include" /I "src" /I "src/include" /I "addons\print" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "grx243 - Win32 Release"
# Name "grx243 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\bgi\arc.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\aspectra.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\bar.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\bar3d.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\bccgrx.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\bccgrx00.h
# End Source File
# Begin Source File

SOURCE=.\src\bgi\bgiext01.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\bgiext02.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\bgimode.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\bgiprint.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\bitblt.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\bitblt1b.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\bitbltnc.c
# End Source File
# Begin Source File

SOURCE=.\src\mouse\bldcurs.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\box.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\boxnc.c
# End Source File
# Begin Source File

SOURCE=.\src\text\buildaux.c
# End Source File
# Begin Source File

SOURCE=.\src\text\buildfnt.c
# End Source File
# Begin Source File

SOURCE=.\src\wideline\ccirc.c
# End Source File
# Begin Source File

SOURCE=.\src\wideline\ccirca.c
# End Source File
# Begin Source File

SOURCE=.\src\wideline\celli.c
# End Source File
# Begin Source File

SOURCE=.\src\wideline\cellia.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\circle.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\circle1.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\circle2.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\circle3.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\circle4.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\clearclp.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\clearctx.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\clearscr.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\clearvp.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\clip.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\closegra.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\clrdev.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\clrinfo.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\clrinlne.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\colorbw.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\colorega.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\colors.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\context.c
# End Source File
# Begin Source File

SOURCE=.\src\text\convfont.c
# End Source File
# Begin Source File

SOURCE=.\src\wideline\custbox.c
# End Source File
# Begin Source File

SOURCE=.\src\wideline\custline.c
# End Source File
# Begin Source File

SOURCE=.\src\wideline\custplne.c
# End Source File
# Begin Source File

SOURCE=.\src\wideline\custpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\cxtinfo.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\cxtinlne.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\detectg.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\dotab8.c
# End Source File
# Begin Source File

SOURCE=.\src\mouse\drawcurs.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\drawpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\text\drawstrg.c
# End Source File
# Begin Source File

SOURCE=.\src\text\drawtext.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\drvinfo.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\drvinlne.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\drvname.c
# End Source File
# Begin Source File

SOURCE=.\src\wideline\drwcpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\drwinlne.c
# End Source File
# Begin Source File

SOURCE=.\src\text\drwstrg.c
# End Source File
# Begin Source File

SOURCE=.\src\text\dumpfont.c
# End Source File
# Begin Source File

SOURCE=.\src\text\dumptext.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\ega4.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\egacolor.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\egavga1.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\ellipse.c
# End Source File
# Begin Source File

SOURCE=.\src\text\epatstrg.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\errmsg.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\fd_win32.c
# End Source File
# Begin Source File

SOURCE=.\src\fonts\fdtable.c
# End Source File
# Begin Source File

SOURCE=.\src\fonts\fdv_bgi.c
# End Source File
# Begin Source File

SOURCE=.\src\fonts\fdv_grx.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\fellipse.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\fframe.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\fgeom.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\fillbox.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\fillboxn.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\fillcir1.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\fillcir2.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\fillcnvx.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\fillell1.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\fillell2.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\fillpatb.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\fillpatt.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\fillpolb.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\fillpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\fillstyl.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\fldfill.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\flood.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\floodfil.c
# End Source File
# Begin Source File

SOURCE=.\src\text\fntinlne.c
# End Source File
# Begin Source File

SOURCE=.\src\text\fontinfo.c
# End Source File
# Begin Source File

SOURCE=.\src\text\fontpath.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\frambox.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\framboxn.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\ftable.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\genblit.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\genellip.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\gengiscl.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\genptscl.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\genstrch.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getbkcol.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getcol.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getdefpa.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getfillp.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getfills.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getgramo.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getimage.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getmaxmo.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getmoran.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getpixel.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\getscl.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getviewp.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\getx.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\gety.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\gmaxcol.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\gmmaxcol.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\gmmaxx.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\gmmaxy.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\gpalsize.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\gpc_init.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\gpc_text.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\graphres.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\herc1.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\hooks.c
# End Source File
# Begin Source File

SOURCE=.\src\image\ialloc.c
# End Source File
# Begin Source File

SOURCE=.\src\image\ibuild.c
# End Source File
# Begin Source File

SOURCE=.\src\image\ifbox.c
# End Source File
# Begin Source File

SOURCE=.\src\image\ihline.c
# End Source File
# Begin Source File

SOURCE=.\src\image\iinverse.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\imagesze.c
# End Source File
# Begin Source File

SOURCE=.\src\image\imginlne.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\instbgid.c
# End Source File
# Begin Source File

SOURCE=.\src\image\iplot.c
# End Source File
# Begin Source File

SOURCE=.\src\image\istretch.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\lfb16.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\lfb24.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\lfb32h.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\lfb32l.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\lfb8.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\lfbbltrv.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\lfbbltvr.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\lfbbltvv.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\line.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\lineb.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\linenc.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\linerel.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\lineto.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\linkall.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\lnestyle.c
# End Source File
# Begin Source File

SOURCE=.\src\text\loadfont.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\majorln1.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\majorln2.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\majorln3.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\majorln4.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\makepat.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\modename.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\modewalk.c
# End Source File
# Begin Source File

SOURCE=.\src\mouse\mouinfo.c
# End Source File
# Begin Source File

SOURCE=.\src\mouse\mouinlne.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\moverel.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\moveto.c
# End Source File
# Begin Source File

SOURCE=.\src\mouse\mscursor.c
# End Source File
# Begin Source File

SOURCE=.\src\utils\ordswap.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\page1.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\page2.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\page3.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\page4.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\page5.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\page6.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\palette.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\patfbits.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\patfbox.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\patfcvxp.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\patfline.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\patfplot.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\patfpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\patternf.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\pattfldf.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\pattline.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\pattpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\text\pattstrg.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\pblitr2r.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\pblitr2v.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\pblitv2r.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\pblitv2v.c
# End Source File
# Begin Source File

SOURCE=.\src\fonts\pc6x8.c
# End Source File
# Begin Source File

SOURCE=.\src\fonts\pc8x14.c
# End Source File
# Begin Source File

SOURCE=.\src\fonts\pc8x16.c
# End Source File
# Begin Source File

SOURCE=.\src\fonts\pc8x8.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\pfcirc.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\pfcirca.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\pfelli.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\pfellia.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\pieslice.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\pixel.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\pixelc.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\plot.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\polyedge.h
# End Source File
# Begin Source File

SOURCE=.\src\shape\polygon.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\polygonb.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\polyline.c
# End Source File
# Begin Source File

SOURCE=.\src\text\propwdt.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\ptcirc.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\ptcirca.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\ptelli.c
# End Source File
# Begin Source File

SOURCE=.\src\pattern\ptellia.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\putimage.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\putpixel.c
# End Source File
# Begin Source File

SOURCE=.\src\draw\putscl.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\ram1.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\ram16.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\ram24.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\ram32h.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\ram32l.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\ram3x8.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\ram4.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\ram8.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\rblit_14.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\rectang.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\regbgidr.c
# End Source File
# Begin Source File

SOURCE=.\src\utils\resize.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\rgbpal_g.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\rgbpal_s.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\rstcrtmd.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\scancnvx.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\scanellp.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\scanpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\sector.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\setbgiwh.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\setbkcol.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\setbusze.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\setcolor.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\setdrvr.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\setmode.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\setrgbc.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\setviewp.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\setwrmod.c
# End Source File
# Begin Source File

SOURCE=.\src\utils\shiftscl.c
# End Source File
# Begin Source File

SOURCE=.\src\shape\solidfil.c
# End Source File
# Begin Source File

SOURCE=.\src\utils\strmatch.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\svga16.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\svga24.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\svga32h.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\svga32l.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\svga4.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\svga8.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text.h
# End Source File
# Begin Source File

SOURCE=.\src\text\text.h
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text1.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text2.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text3.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text4.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text5.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text6.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text7.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text8.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\text9.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\texta.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\textb.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\textc.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\textd.c
# End Source File
# Begin Source File

SOURCE=.\src\utils\tmpbuff.c
# End Source File
# Begin Source File

SOURCE=.\src\bgi\txtlnest.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ubox.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ucbox.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uccirc.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uccirca.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ucelli.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ucellia.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ucirc.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ucirca.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ucircf.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ucircfa.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ucline.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ucpolyg.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ucpolyl.c
# End Source File
# Begin Source File

SOURCE=.\src\user\udrwchar.c
# End Source File
# Begin Source File

SOURCE=.\src\user\udrwstrg.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uelli.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uellia.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uellif.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uellifa.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ufcpolyg.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ufillbox.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uflood.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ufpolyg.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uframbox.c
# End Source File
# Begin Source File

SOURCE=.\src\user\ugetwin.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uhline.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uline.c
# End Source File
# Begin Source File

SOURCE=.\src\text\unloadfn.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upbox.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upcirc.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upcirca.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upelli.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upellia.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upfbox.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upfcirc.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upfcirca.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upfcpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upfelli.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upfellia.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upfflood.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upfline.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upfplot.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upfpolyg.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upixel.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upixelc.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upline.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uplot.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upolygon.c
# End Source File
# Begin Source File

SOURCE=.\src\user\upolylin.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uppolyg.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uppolyl.c
# End Source File
# Begin Source File

SOURCE=.\src\user\usercord.c
# End Source File
# Begin Source File

SOURCE=.\src\user\usetwin.c
# End Source File
# Begin Source File

SOURCE=.\src\user\utextxy.c
# End Source File
# Begin Source File

SOURCE=.\src\user\uvline.c
# End Source File
# Begin Source File

SOURCE=.\src\vdrivers\vd_mem.c
# End Source File
# Begin Source File

SOURCE=.\src\vdrivers\vd_win32.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\version.c
# End Source File
# Begin Source File

SOURCE=.\src\fdrivers\vga8x.c
# End Source File
# Begin Source File

SOURCE=.\src\setup\viewport.c
# End Source File
# Begin Source File

SOURCE=.\src\vdrivers\vtable.c
# End Source File
# Begin Source File

SOURCE=.\src\mouse\w32inp.c
# End Source File
# Begin Source File

SOURCE=.\src\mouse\w32keys.c
# End Source File
# Begin Source File

SOURCE=.\src\misc\w32misc.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
