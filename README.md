# TouchCPLib

A touch-enabled GUI interface based on SDL and libTS. It provides a simple desktop-free UI for your embedded Raspberry projects.

The basic usage of this library relies upon the Application class.
You first create one or more scenes that inherit from the `GraphicsScene` class.
You can use the provided objects (such as the Button, ImageButton, XYPlot etc.) or create custom ones. Refer to the existing implementations for guidance.

After you create your instances of the objects you call `addObject` on your scene to let them be drawn to the screen. The scene will take care of deleting them when destroyed.

You then create an instance of the `Application` class before you instanciate your scenes.
After this, you instanciate your scene, that will automatically register itself in the application SceneManager, and finally call the `show` method.

```c++
Application app(...);

MainScene mainScene;
mainScene.show();

app.run();
```