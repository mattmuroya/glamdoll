#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include <glad/glad.h>

#include "vbo.h"

class VertexArrayObject
{
    GLuint id;

public:
    VertexArrayObject();
    ~VertexArrayObject();
    void bind();
    void unbind();
    void add(VertexBufferObject&, GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);
};

#endif
