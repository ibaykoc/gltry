#include "ElementBuffer.h"
#include "Renderer.h"

ElementBuffer::ElementBuffer(const void* data, unsigned int count): m_Count(count){

    glGenBuffers(1, &m_RendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer(){
    glDeleteBuffers(1, &m_RendererId);
}

void ElementBuffer::Bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
}

void ElementBuffer::Unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}