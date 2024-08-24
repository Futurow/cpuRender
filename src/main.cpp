#include "include/window.hpp"
int main()
{
    Window window = Window(640, 480);
    window.open();
    window.play();
    window.close();
    return 0;
}