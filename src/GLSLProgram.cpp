#include "GLSLProgram.h"

GLSLProgram::GLSLProgram(std::string vertexShaderFilePath, std::string fragmentShaderFilePath) {
    std::cout << "GLSLProgram constructed" << std::endl;
    std::string line;
    std::string src;
    std::ifstream ishader(vertexShaderFilePath);
    if(ishader.is_open()){
        while (std::getline(ishader, line))
        {
            src = src + line + "\n";
        }

        std::cout << "Vertex Shader Source: \n" << src << std::endl;

        ishader.close();
    } else {
        std::cerr << "ERROR::GLSLProgram::Failed to open vertex file" << std::endl;
    }

    const char * vertSrc = src.c_str();
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertSrc, NULL);
    glCompileShader(vertexShaderId);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (success) {
        std::cout << "Compile vertex succeed\n" << std::endl;
    } else {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    line = "";
    src = "";
    ishader.open(fragmentShaderFilePath);
    if(ishader.is_open()){
        while (std::getline(ishader, line))
        {
            src = src + line + "\n";
        }

        std::cout << "Fragment Shader Source: \n" << src << std::endl;

        ishader.close();
    } else {
        std::cerr << "ERROR::GLSLProgram::Failed to open vertex file" << std::endl;
    }
    const char * fragSrc = src.c_str();
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragSrc, NULL);
    glCompileShader(fragmentShaderId);
    // check for shader compile errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (success) {
        std::cout << "Compile fragment succeed\n" << std::endl;
    } else {
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    _id = glCreateProgram();
    glAttachShader(_id, vertexShaderId);
    glAttachShader(_id, fragmentShaderId);
    glLinkProgram(_id);
    // check for linking errors
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (success) {
        std::cout << "Link shader succeed\n" << std::endl;
    } else {
        glGetProgramInfoLog(_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

GLSLProgram::~GLSLProgram() {
    glDeleteProgram(_id);
}

void GLSLProgram::Use() {
    glUseProgram(_id);
}

void GLSLProgram::Unuse() {
    glUseProgram(0);
}