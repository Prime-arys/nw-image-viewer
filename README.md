# nw-image-viewer

An image viewer for the numworks calculator

Omega is needed : https://getomega.dev/

Usage : 
- Python 3 required with Pillow & colormap.
- Images (in **"d_img"**) must be 320x240px in RGB 8bpc, and numbered as in the example (0-XX).
- Use **"wnt2bin2.py"** to generate the **".bin"** file.
- **"nw-img-vw"** allows you to display pictures, short videos/animations, and you can secure some of them with a pin code.
- (in app, use "menu" button to exit)

To build and use you will need : 
- First of all, follow **step 1** [here](https://www.numworks.com/resources/engineering/software/build/). (on Windows add [dfu-util](http://dfu-util.sourceforge.net/) to Msys2)
- Then set up : https://github.com/Omega-Numworks/Omega-External,<br/>
and integrate **"nw-img-vw"** (don't forget to integrate your **".bin"** files to your package) . 

