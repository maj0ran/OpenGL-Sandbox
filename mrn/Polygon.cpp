//
// Created by mrn on 09.03.2019.
//

#include "Polygon.h"

namespace mrn {
    Polygon::Polygon() {

    }

    Polygon::~Polygon() {

    }

    void mrn::Polygon::addVertex(Vertex v) {
        this->vertices.push_back(v);
    }

    void Polygon::initBuf() {
        glGenBuffers(1, &this->array_buf);
        glBindBuffer(GL_ARRAY_BUFFER, array_buf);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(mrn::Vertex), &this->vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->index_buf);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32), &indices[0], GL_STATIC_DRAW);
    }


    void Polygon::addTriangleIndices(uint32 p1, uint32 p2, uint32 p3) {
        this->indices.push_back(p1);
        this->indices.push_back(p2);
        this->indices.push_back(p3);
    }
}
