//
// Created by mrn on 09.03.2019.
//

#include "Mesh.h"

namespace mrn {
    Mesh::Mesh() {

    }

    Mesh::~Mesh() {

    }

    void mrn::Mesh::addVertex(Vertex v) {
        this->vertices.push_back(v);
    }

    void Mesh::initBuf() {

        glGenVertexArrays(1, &this->array_object);
        glBindVertexArray(this->array_object);

        glGenBuffers(1, &this->vertex_buf);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(mrn::Vertex), &this->vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->index_buf);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32), &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);


    }


    void Mesh::addTriangleIndices(uint32 p1, uint32 p2, uint32 p3) {
        this->indices.push_back(p1);
        this->indices.push_back(p2);
        this->indices.push_back(p3);
    }
}
