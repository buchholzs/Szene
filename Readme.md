# PlushPlayer
A program to view 3D scenes written in XML using the 3D plush library.

# Matedit
A material editor which allows interactive manipulating materials of objects in a scene.  

# What is the Plush library?
Both programs use the [3D plush library](/plush/pl_api.html) which was formerly located [here](http://www.nullsoft.com/free/plush/). For the GUI, I used the [Depui](/depui/homepage/depui.htm) library. The graphics library is [GRX](/contrib/grx248/doc/grx248um.html).

# History
I started working on this project in 2002, so the graphics are outdated by today's standards. The original target platform was DJGPP DOS. Later I switched to Windows as main target platform. Linux is still under construction. In the meantime, I haven't worked on the project for a long time. Anyway, I want to finally finish the project, achieve the goals of the time and practice C++ by the way.


# Usage
These two programs run under Windows.
To start, use

- `PlushPlayer.exe` or
- `Matedit2.exe`


## PlushPlayer
![PlushPlayer with kepler.scx](/assets/img/3.jpeg)

You can load any *.scx (Scene XML) file from the "scenes" folder.
When you start PlushPlayer, it shows a file open dialog to select a scene file.

In the scene, you can navigate using the mouse and the following keys:
-  w - step forward
- a - step left
- s - step backward
- d - step right
- r - reload a previously loaded scene
- F1 - popup the key help window
- F3 - popup the file open dialog.

## Matedit
![Matedit with standard.scx](/assets/img/1.jpeg)

You can modify the material using various sliders. Load a scene file from the "scenes" folder or use the default standard.scx file. 
Click on any of the materials in the materials list and change the properties on the fly with the slider.