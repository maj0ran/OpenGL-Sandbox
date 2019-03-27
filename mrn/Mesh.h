//
// Created by mrn on 09.03.2019.
//

#ifndef OPENGL_SANDBOX_POLYGON_H
#define OPENGL_SANDBOX_POLYGON_H


#include <vector>
#include "Vertex.h"
#include "../include/glad/glad.h"


namespace mrn {

    using namespace glm;

    class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<uint32> indices;

        GLuint array_object;
        GLuint vertex_buf;
        GLuint index_buf;

        Mesh();
        ~Mesh();

        void addVertex(Vertex v);
        void addTriangleIndices(uint32 p1, uint32 p2, uint32 p3);

        void initBuf();

    };

}
#endif //OPENGL_SANDBOX_POLYGON_H
