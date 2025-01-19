#include "vbo.h"

VertexBufferObject::VertexBufferObject()
{
    glGenBuffers(1, &id);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &id);
}

void VertexBufferObject::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
};

void VertexBufferObject::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::upload(const int size, const float* data)
{
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    this->unbind();
}
