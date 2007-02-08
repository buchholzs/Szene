# Microsoft Developer Studio Project File - Name="scenelib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=scenelib - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "scenelib.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "scenelib.mak" CFG="scenelib - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "scenelib - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "scenelib - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "scenelib - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "scenelib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "scenelib___Win32_Debug"
# PROP BASE Intermediate_Dir "scenelib___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "..\plush\src" /I "..\Expat-1.95.2\Source\lib" /I "..\depui\include" /I "..\contrib\grx243\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\scene.lib"

!ENDIF 

# Begin Target

# Name "scenelib - Win32 Release"
# Name "scenelib - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\Command.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Controller.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FlyMode.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Hud.cpp
# End Source File
# Begin Source File

SOURCE=.\src\HudRefreshCmd.cpp
# End Source File
# Begin Source File

SOURCE=.\src\MoveMode.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sc_tokens.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Scene.cpp
# End Source File
# Begin Source File

SOURCE=.\src\SceneDesktop.cpp
# End Source File
# Begin Source File

SOURCE=.\src\WalkMode.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\Command.h
# End Source File
# Begin Source File

SOURCE=.\src\Controller.h
# End Source File
# Begin Source File

SOURCE=.\src\Desktop.h
# End Source File
# Begin Source File

SOURCE=.\src\FlyMode.h
# End Source File
# Begin Source File

SOURCE=.\src\Hud.h
# End Source File
# Begin Source File

SOURCE=.\src\HudRefreshCmd.h
# End Source File
# Begin Source File

SOURCE=.\src\MoveMode.h
# End Source File
# Begin Source File

SOURCE=.\src\sc_tokens.h
# End Source File
# Begin Source File

SOURCE=.\src\Scene.h
# End Source File
# Begin Source File

SOURCE=.\src\SceneDesktop.h
# End Source File
# Begin Source File

SOURCE=.\src\WalkMode.h
# End Source File
# End Group
# End Target
# End Project
