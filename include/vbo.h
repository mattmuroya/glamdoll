#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <glad/glad.h>

class VertexBufferObject
{
    GLuint id;

public:
    VertexBufferObject();
    ~VertexBufferObject();
    void bind();
    void unbind();
    void upload(const int, const float*);
};

#endif
