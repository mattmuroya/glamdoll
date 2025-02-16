// my_array.h
#ifndef MY_ARRAY_H
#define MY_ARRAY_H


float vertices[] = {
    // Front face
    -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 1.0f,  1.0f, 1.0f, -1.0f, 1.0f, 1.0f,

    // Back face
    -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f,

    // Left face
    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, -1.0f,  1.0f, -1.0f,

    // Right face
    1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 1.0f,  1.0f, 1.0f, -1.0f,  1.0f,

    // Top face
    -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f,
    -1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,

    // Bottom face
    -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,  1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  1.0f, -1.0f, -1.0f, 1.0f
};

float colors[] = {
    // Front face
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    // Back face
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    // Left face
    1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    // Right face
    1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    // Top face
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    // Bottom face
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
};

float normals[] = {
    // Front face
    0.0f,  0.0f,  1.0f, 0.0f,  0.0f,  1.0f,        0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,        0.0f,  0.0f,  1.0f,        0.0f,  0.0f,  1.0f,

    // Back face
    0.0f,  0.0f, -1.0f,        0.0f,  0.0f, -1.0f,        0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,        0.0f,  0.0f, -1.0f,        0.0f,  0.0f, -1.0f,

    // Left face
    -1.0f,  0.0f,  0.0f,        -1.0f,  0.0f,  0.0f,        -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,        -1.0f,  0.0f,  0.0f,        -1.0f,  0.0f,  0.0f,

    // Right face
    1.0f,  0.0f,  0.0f,        1.0f,  0.0f,  0.0f,        1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,        1.0f,  0.0f,  0.0f,        1.0f,  0.0f,  0.0f,

    // Top face
    0.0f,  1.0f,  0.0f,        0.0f,  1.0f,  0.0f,        0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,        0.0f,  1.0f,  0.0f,        0.0f,  1.0f,  0.0f,

    // Bottom face
    0.0f, -1.0f,  0.0f,        0.0f, -1.0f,  0.0f,        0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,        0.0f, -1.0f,  0.0f,        0.0f, -1.0f,  0.0f
};

#endif