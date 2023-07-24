#include <iostream>

#include "../include/windowHandler.h"
#include "../include/config.h"
#include "../include/algorithms/bezier.h"

WindowHandler* pWindow = nullptr;
Renderer* pRenderer = nullptr;

int main()
{
    pWindow = new WindowHandler(WINDOW_X_SIZE, WINDOW_Y_SIZE);
    pRenderer = new Renderer(SHADER_PATH);

    Points points = Bezier::quadraticBezier(Vec2<float>(10.0f, 256.0f), Vec2<float>(128.0f, 32.0f), Vec2<float>(256.0f, 256.0f), 50);
    while (pWindow->update())
    {
        /*if (!pRenderer->draw(&points))
            break;*/
    }

    delete pRenderer;
    delete pWindow;

    return 0;
}
