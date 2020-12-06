# TouchCPLib

A control panel library written in C++ using the SDL library and TSLib, designed to run on a 3.5 Raspberry Pi touchscreen.

It aims at simplifying the control of external instrumentation, and collect and optionally display data from it.

The choice of SDL and not other X11 compatible desktop solutions is to avoid the overhead of a desktop and
to have the interface quickly loaded at boot.

The 3.5" TFT display (a waveshare-like one) grants a discrete amount of pixels to work with (320x480), 
and the touch interaction is quick and responsive.
The animations, however, are sloppy because of the very low refresh rate (around 5 Hz, supply voltage dependent).

This doesn't prevent us from using the display as a control panel to command some external instrument,
and even to display data and charts on it.

The code is not so bad, I created some wrapper classes for graphic objects, touch interaction, scenes.
The scenes are the fundamental part of the interface, and they represent a full screen view.

The scenes are created at the start of the program, and they can be switched at any time by using the SceneManager object
provided in the constructor of each scene.
The touch interaction works by searching for touch enabled objects in the currentScene, and calling a function set in them.
To set the callback function you can call the appropriate method on the object.

The objects can be touch-disabled, and they can propagate the touch event to other
objects placed below them, by setting the properties through the object methods.

The scenes have zero or more objects in them that get drawn by the main loop. The scenes do not draw anything by themselves,
only the children objects get drawn.

The object classes created as of now are simple buttons, and some animations of waves. There's also a
grid helper class to help position the square button items on the screen in a 5x3 grid.

The usage is pretty simple. First subclass a `GraphicsScene` object and add all the graphic objects you need to it, then in your main (or anywhere else)
create an Application and pass the MainScene you just created to it. Then call the `run` method to start the main loop.

```
MainScene mainScene;
Application app(&mainScene, ...);
app.run();
```