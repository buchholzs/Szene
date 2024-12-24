# PlushPlayer
A program to view 3D scenes written in XML using the 3D plush library.

# Matedit
A material editor which allows interactive manipulating materials of objects in a scene.  

# What is the Plush library?
Both programs use the [3D plush library](/plush/pl_api.html) which was formerly located [here](http://www.nullsoft.com/free/plush/). For the GUI, I used the [Depui](/depui/homepage/depui.htm) library. The graphics library is [GRX](/contrib/grx248/doc/grx248um.html).

# History
I started working on this project in 2002, so the graphics might be outdated by today's standards. The original target platform was DJGPP DOS. Later I switched to Windows as main target platform. Linux versions are also available. In the meantime, I haven't worked on the project for a long time. Anyway, I have now finally finished the project, achieved the goals of the time and practiced C++ by the way.


# Usage
These two programs run under Windows and Linux.
To start, use

- `PlushPlayer.exe` / `PlushPlayer` or
- `MatEdit.exe` / `MatEdit`


## PlushPlayer
![PlushPlayer with kepler.scx](/assets/img/3.jpeg)

You can load any *.scx (Scene XML) file from the "scenes" folder.
When you start PlushPlayer, it shows a file open dialog to select a scene file.

In the scene, you can navigate using the mouse and the following keys:
|Key        | Description           |
|-----------|-----------------------|
| `<Esc>`   | ingame menu           |
| w         | move forward          |
| a         | move left             |
| s         | move backward         |
| d         | move right            |
| r         | reload scene          |
| q         | quit                  |
| `<space>` | play/pause            |
| F1        | Key Help              |
| F3        | Load Scene File       |
| F9        | Set move mode to walk |
| F10       | Set move mode to fly  |

## Matedit
![Matedit with standard.scx](/assets/img/1.jpeg)

You can modify the material using various sliders. Load a scene file from the "scenes" folder or use the default standard.scx file. 
Click on any of the materials in the materials list and change the properties on the fly with the slider.