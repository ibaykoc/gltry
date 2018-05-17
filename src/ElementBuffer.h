#pragma once

class ElementBuffer {
    private:
        unsigned int m_RendererId;
        unsigned int m_Count;
    public:
        ElementBuffer(const void* data, unsigned int count);
        ~ElementBuffer();

        void Bind() const;
        void Unbind() const;

        inline unsigned int getCount() const {return m_Count;}
};