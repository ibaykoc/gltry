#include "Window.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h" 
#include "GLSLProgram.h"
#include <iostream>

int main(void) {
    Window window(640, 480, "WINDOW");
    window.Initialize();

    GLSLProgram program("src/glsl/a.vs", "src/glsl/a.fs");   

    float positions[12] = {
        -0.5f,  0.5f, 0.0f,     // Top Left
         0.5f,  0.5f, 0.0f,     // Top Right
         0.5f, -0.5f, 0.0f,     // Bottom Right
        -0.5f, -0.5f, 0.0f      // Bottom Left
    };
    unsigned int indices[6] = {
        0, 1, 2,    // First Triangle
        0, 2, 3     // Second Triangle
    };   

    unsigned int vaoId;
    glGenVertexArrays(1, &vaoId);

    glBindVertexArray(vaoId);
    
    VertexBuffer vb(positions, sizeof(positions));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);

    ElementBuffer eb(indices, 6);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        window.Clear();

    while(!window.isShouldClose() && !glfwWindowShouldClose(window.GetGlfwWindow())){
        program.Use();
        window.Clear();
        vb.Bind();
        eb.Bind();
        glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
        window.SwapBuffers();
        window.ProcessInput();
    }
}