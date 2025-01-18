#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <string>

#include <glad/glad.h>

class VertexBufferObject
{
public:
    GLuint id; // Vertex buffer object handle

    // Constructor
    VertexBufferObject()
    {
        glGenBuffers(1, &id);
    }

    // Destructor
    ~VertexBufferObject()
    {
        glDeleteBuffers(1, &id);
    }

    // Bind this vertex buffer object
    void bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    };

    // Unbind this vertex buffer object
    void unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void upload(const int size, const float* data)
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

#endif
