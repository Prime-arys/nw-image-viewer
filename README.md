# nw-image-viewer (old)
**Picture in the build-up**

An image viewer for the numworks calculator

Omega is needed : https://getomega.dev/

Usage : 
- Python 3 required with Pillow & colormap.
- Images (in **"d_img"**) must be 320x240px in RGB 8bpc, and numbered as in the example (0-XX).
- Use **"wnt2.py"** to generate the **"dwc.h"** file.
- **"nw-img-vw"** is a gallery (up to ~20 images), use digits 0-9 and parentheses () for navigation.
- **"nw-vid-vw"** allows you to make short videos/animations.
- (in app, use "menu" button to exit)

To build and use you will need : 
- First of all, follow **step 1** [here](https://www.numworks.com/resources/engineering/software/build/). (on Windows add [dfu-util](http://dfu-util.sourceforge.net/) to Msys2)
- Then set up : https://github.com/Omega-Numworks/Omega-External,<br/>
and integrate **"nw-img-vw"** and/or **"nw-vid-vw"**.

