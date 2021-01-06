#include "Window.h"

int main()
{
    Window window;

    // pêtla programu
    while (window.windowIsOpen())
    {
        window.update();
        window.render();
    }

    return 0;
}