#include "../include/windowHandler.h"

#include <stdexcept>

WindowHandler::WindowHandler(uint32_t x, uint32_t y)
{
    if (!glfwInit())
    {
        printf("Could not initialize GLFW!\n");
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(x, y, "Graphics Algorithms", nullptr, nullptr);
    if (!mWindow)
    {
        glfwTerminate();
        printf("Could not create window!\n");
        exit(1);
    }

    glfwMakeContextCurrent(mWindow);
}

WindowHandler::~WindowHandler()
{
    glfwDestroyWindow(mWindow);
    mWindow = nullptr;

    glfwTerminate();
}

void WindowHandler::setRenderer(Renderer *renderer)
{
    mRenderer = renderer;
}

bool WindowHandler::update()
{
    if (glfwWindowShouldClose(mWindow))// || !mRenderer)
        return false;

    glfwSwapBuffers(mWindow);
    glfwPollEvents();

    return true;
}
