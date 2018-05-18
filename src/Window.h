#pragma once
#include <string>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window {
private:
    GLFWwindow* _window;
    int _width;
    int _height;
    std::string _title;
    bool _shoudClose;
public:
    GLFWwindow* GetGlfwWindow();

    bool isShouldClose();

    Window(int width, int height, std::string title);

    int Initialize();

    void Clear();
    void SwapBuffers();

    void OnFramebufferSizeChange(int width, int height);
    void ProcessInput();

    void Close();

    ~Window();
};