#include "vao.h"

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &id);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &id);
}

void VertexArrayObject::bind()
{
    glBindVertexArray(id);
};

void VertexArrayObject::unbind()
{
    glBindVertexArray(0);
}

void VertexArrayObject::add(
    VertexBufferObject& vbo, // VBO to attach
    GLuint index,            // Attribute position (for shader `in`)
    GLint size,              // Number of array elements per attribute
    GLenum type,             // Array element type
    GLboolean normalized,    // Whether to normalize
    GLsizei stride,          // Distance between starting bytes of consecutive attributes
    const GLvoid* offset)    // Offset of first attribute in buffer
{
    this->bind();
    vbo.bind();
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
    this->unbind();
}
