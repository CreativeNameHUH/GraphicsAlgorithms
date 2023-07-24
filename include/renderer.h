#ifndef GRAPHICSALGORITHMS_RENDERER_H
#define GRAPHICSALGORITHMS_RENDERER_H

#include <glad.h>

#include "math/vec2.h"

class Renderer
{
public:
    explicit Renderer(const std::string& shaderPath);
    ~Renderer();

    bool draw(const Points* points);

private:
    GLuint mProgram = 0;

    static GLuint compileShader(GLenum shaderType, const std::string& shaderPath);
};


#endif //GRAPHICSALGORITHMS_RENDERER_H
