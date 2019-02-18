//
// Created by mrn on 17.02.2019.
//

#ifndef OPENGL_SANDBOX_VERTEXDATA_H
#define OPENGL_SANDBOX_VERTEXDATA_H


float triangle[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
};

float rectangle[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
};

unsigned int rectangleIndices[] = {
        0, 1, 2,
        0, 2, 3
};

float two_triangles[] = {
        // left triangle
        -0.6f, -0.3f, 0.0f,
        -0.3f, 0.0f, 0.0f,
        0.0f, -0.3f, 0.0f,
        // right triangle
        0.0f, -0.3f, 0.0f,
        0.3f, 0.0f, 0.0f,
        0.6f, -0.3f, 0.0f
};

float firstTriangle[] = {
        -0.6f, -0.3f, 0.0f,
        -0.3f, 0.0f, 0.0f,
        0.0f, -0.3f, 0.0f,
};

float secondTriangle[] = {
        // position             // color
        0.0f, -0.3f, 0.0f,      1.0f, 0.0f, 0.0f,
        0.3f, 0.0f, 0.0f,       0.0f, 1.0f, 0.0f,
        0.6f, -0.3f, 0.0f,      0.0f, 0.0f, 1.0f
};

#endif //OPENGL_SANDBOX_VERTEXDATA_H
