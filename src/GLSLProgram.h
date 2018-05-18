#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>

class GLSLProgram {
private:
    GLuint _id;
public:
    GLSLProgram(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);
    ~GLSLProgram();
    void Use();
    void Unuse();
};