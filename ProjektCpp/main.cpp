#include "Window.h"

int main()
{
    Window window;

    // p�tla programu
    while (window.windowIsOpen())
    {
        window.update();
        window.render();
    }

    return 0;
}