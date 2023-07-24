#ifndef GRAPHICSALGORITHMS_WINDOWHANDLER_H
#define GRAPHICSALGORITHMS_WINDOWHANDLER_H

#include "renderer.h"
#include <glfw3.h>

class WindowHandler
{
public:

    WindowHandler(uint32_t x, uint32_t y);
    ~WindowHandler();

    void setRenderer(Renderer* renderer);

    bool update();

private:
    GLFWwindow* mWindow = nullptr;

    Renderer* mRenderer = nullptr;
};


#endif //GRAPHICSALGORITHMS_WINDOWHANDLER_H
