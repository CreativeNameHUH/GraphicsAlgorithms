#include "../include/renderer.h"

#include <fstream>
#include <string>

Renderer::Renderer(const std::string& shaderPath)
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, shaderPath + "shader.vert");
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaderPath + "shader.frag");

    if (!(vertexShader & fragmentShader))
        return;

    mProgram = glCreateProgram();
    if (!mProgram)
    {
        printf("Could not compile shaders!\n");
        return;
    }

    glAttachShader(mProgram, vertexShader);
    glAttachShader(mProgram, fragmentShader);
    glLinkProgram(mProgram);

    GLint error;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &error);
}

Renderer::~Renderer()
{
    glUseProgram(0);
    glDeleteProgram(mProgram);
}

bool Renderer::draw(const Points *points)
{
    return false;
}

GLuint Renderer::compileShader(GLenum shaderType, const std::string& shaderPath)
{
    std::ifstream file(shaderPath);
    std::string shader;
    while (!file.eof())
        std::getline(file, shader);
    file.close();

    if (shader.empty())
        return 0;

    GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, reinterpret_cast<const GLchar *const *>(shader.c_str()), nullptr);
    glCompileShader(shaderId);

    GLint error;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &error);
    if (!error)
    {
        GLint log;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &log);
        std::string errorString(log, '\0');
        glGetShaderInfoLog(shaderId, log, nullptr, &errorString[0]);
        printf("Shader compilation error: %s\n", errorString.c_str());

        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}
