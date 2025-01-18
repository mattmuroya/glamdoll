#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include <iostream>

#include <glad/glad.h>

#include "vbo.cpp"

class VertexArrayObject
{
public:
    GLuint id; // Vertex attribute array handle

    // Constructor
    VertexArrayObject()
    {
        glGenVertexArrays(1, &id);
    }

    // Destructor
    ~VertexArrayObject()
    {
        glDeleteVertexArrays(1, &id);
    }

    // Bind this vertex array object
    void bind()
    {
        glBindVertexArray(id);
    };

    // Unbind this vertex array object
    void unbind()
    {
        glBindVertexArray(0);
    }

    // Attach a vertex buffer object to this vertex array object
    void add(
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
};

#endif
