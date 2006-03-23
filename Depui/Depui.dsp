# Microsoft Developer Studio Project File - Name="Depui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Depui - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Depui.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Depui.mak" CFG="Depui - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Depui - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "Depui - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Depui - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "." /I "C:\Projekte\Szene\Depui\INCLUDE" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Depui - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /I "C:\Projekte\Szene\Depui\INCLUDE" /I "C:\Projekte\Szene\Depui\SOURCE" /I "C:\Projekte\Szene\contrib\grx243\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
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

# Name "Depui - Win32 Release"
# Name "Depui - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\SOURCE\OBJECT\ALERT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DEBUG\ALLOC.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\ANIMATE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\BAR.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\BLIT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\BLITFS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\BLITS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\BLITTS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\BTN.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\BTNCANC.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\BTNEXIT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\BTNOK.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\BTNPUSH.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\BTNRADIO.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\BTNTOGG.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PLATFORM\BUFFDBL.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\CHECK.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\CHECK1.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\CHECKBOX.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\CLIP.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\CLIPBLIT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\CLOSE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\CURSOR.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\DECORATE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\DEFSIZE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DESKTOP\DESKTOP.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\DIRECT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\dirent.c
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DRAGDROP.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DRAW\DRAW.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\EDITAREA.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\EDITLINE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\EDITOR.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\EDITSCRL.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PLATFORM\EMPTYIN.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PLATFORM\EMPTYOUT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PLATFORM\EMPTYSYS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\EVENT\EVENT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\EVENT\EVENT2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FILE1.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FILE2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FILE3.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FILE4.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\FILESEL.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FINDFIRS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\EVENT\FOCUS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FONT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FONTAA.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FONTADD.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FONTDEF.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FONTDEF2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FONTDEF3.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FONTDEF4.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FONTDEF5.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FONTDUMP.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\FONTPIX.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\FRAME.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\FRAME1.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\FRAME2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GEOMETRY\GEOM1.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GEOMETRY\GEOM2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GEOMETRY\GEOMENCL.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GEOMETRY\GEOMETRY.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GEOMETRY\GEOMJC.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GEOMETRY\GEOMJC2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\GETPIX.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\GETPIXS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GLOBALS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\HIDE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\HLINE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\HLINES.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IBLIT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IHLINE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\ILOAD.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\ILOAD2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\ILOADBMP.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\ILOADPCX.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IMAGE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IMAGE1.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IMAGE16.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IMAGE24.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IMAGE32.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IMAGE4.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IMAGE8.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IRECT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\IVLINE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\LIST.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\LISTAREA.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\LISTDEF.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\MENU.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\MENUPD.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\SUPPORT\MOUSE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DRAW\MOVE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\MOVER.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\OBJECT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DESKTOP\OBJEXIST.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\OBJINS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\OBJNEW.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\OBJREM.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\OBJSORT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\OBJZOR2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\OBJZORD.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\PANEL.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\PIXEL.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\PIXELCL.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\PIXELCL2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\PIXELCLT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\PIXELS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\PIXELT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\PIXELTS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PLATFORM\PLATFORM.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PLATFORM\PLATIN.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PLATFORM\PLATOUT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\PLATFORM\PLATSYS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\POINTER\POINTER.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\POINTER\POINTHLD.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\POINTER\POINTMVE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DESKTOP\POP.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\POSMCH.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\POSMCW.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\POSMOVE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\POSMX.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\POSMY.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\POSSIZE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\EVENT\QUEUE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\RADIO.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\RADIOGRP.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\RECT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\RECTS.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DRAW\REGION.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DRAW\REGION2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DRAW\REGION3.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DRAW\REGION4.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\RELATION.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\RESIZE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\RESIZE2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\DESKTOP\ROOT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\SCROLL.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\SCROLL2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\SLIDER.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\SLIDERH.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\SLIDERV.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\STATICT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\STATICT2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\STATICT3.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXT.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXT1.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXT2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXT3.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXT4.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXT5.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXT6.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXTARE2.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXTARE3.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXTARE4.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXTAREA.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXTARSC.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXTLIN3.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXTLIN4.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\TEXTLINE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\VLINE.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\GRAPHICS\VLINES.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\WINDOW.C
# End Source File
# Begin Source File

SOURCE=.\SOURCE\OBJECT\WINDOW2.C
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\_CONFIG.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\ALERT.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\ANIMATE.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\BAR.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\BUTTON.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\CONFIG.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\CURSOR.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\DEFSIZE.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\DEPUI.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\DIRECT.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\DRAGDROP.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\EDIT.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\EDITOR.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\FILESEL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\LIST.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\LISTDEF.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\MACROS.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\MENU.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\MOVER.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\OBJECT.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\PANEL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\RADIOGRP.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\SCROLL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\SLIDER.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\STATICT.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\TEXT.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\TYPES.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DEPUI\OBJECT\WINDOW.H
# End Source File
# End Group
# End Target
# End Project
