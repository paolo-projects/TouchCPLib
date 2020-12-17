#include <iostream>

#include <TouchCP/Application.h>
#include <TouchCP/GraphicsScene.h>
#include <TouchCP/Button.h>

class SampleScene : public GraphicsScene
{
public:
    SampleScene()
    {
        Button *simpleButton = new Button();
        simpleButton->setFillColor({255, 255, 255, 255});
        simpleButton->setGeometry({50, 50, 50, 50});
        simpleButton->setTouchCallback([]() {
            std::cout << "You pressed me!\n";
        });
        addObject(simpleButton);
    }
};

int main(int argc, const char **argv)
{
    Application app(480, 320, {0, 0, 0, 0xFF}, "/dev/event/input0", "/dev/tty0", 30);
    SampleScene scene;
    scene.show();

    app.run();
}