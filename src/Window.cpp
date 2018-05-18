#include "Window.h"

// Window size callback
Window* windowPtr = nullptr;
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    if(windowPtr) {
        windowPtr->OnFramebufferSizeChange(width, height);
    }
}

Window::Window(int width, int height, std::string title):_width(width), _height(height), _title(title) {
    std::cout << "Window Constructed" << std::endl;
    windowPtr = this;
}

GLFWwindow* Window::GetGlfwWindow() {
    return _window;
}

bool Window::isShouldClose() {
    return _shoudClose;
}

int Window::Initialize() {
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Set context to use modern openGl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    // Initialize glew after the context is made
    if (glewInit() == GLEW_OK){
        std::cout << "Window using GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "Window using GL version: " << glGetString(GL_VERSION) << std::endl;
    } else {
        std::cout << "Glew Init failed" << std::endl;
        return -1;
    }

    // Specify openGl Viewport
    glViewport(0,0,_width,_height);
    glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);
    _shoudClose = false;
    return 0;
}

void Window::Clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(_window);
}

void Window::ProcessInput() {
    glfwPollEvents();
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        _shoudClose = true;
}

void Window::Close() {
    _shoudClose = true;
}

void Window::OnFramebufferSizeChange(int width, int height) {
    std::cout << "Framebuffer size changed:(" << width << ", " << height << ")" << std::endl;
    _width = width;
    _height = height;
    glViewport(0,0, _width, _height);
    // glClear(GL_COLOR_BUFFER_BIT);
    // glfwSwapBuffers(_window);
}

Window::~Window() {
    std::cout << "Window deconstructed" << std::endl;
    windowPtr = nullptr;
    glfwDestroyWindow(_window);
    glfwTerminate();
}