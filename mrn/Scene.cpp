//
// Created by mrn on 11.03.2019.
//

#include "Scene.h"

namespace mrn {

    Scene::Scene() {
        cam = Camera();
        objects = std::vector<Model>();
    }

    Scene::~Scene() {

    }

    void Scene::render() {

        cam.update();

        for(Model& o : objects) {
            o.shader->use();
            GLint proj_loc = glGetUniformLocation(o.shader->id, "projection");
            GLint view_loc = glGetUniformLocation(o.shader->id, "view");
            GLint trans_loc = glGetUniformLocation(o.shader->id, "transform");

            glUniformMatrix4fv(trans_loc, 1, GL_FALSE, value_ptr(o.getTranslationMat()));
            glUniformMatrix4fv(view_loc, 1, GL_FALSE, value_ptr(cam.view));
            glUniformMatrix4fv(proj_loc, 1, GL_FALSE, value_ptr(cam.projection));

            glBindVertexArray(o.mesh->array_object);
            glDrawElements(GL_TRIANGLES, o.mesh->indices.size() * 3, GL_UNSIGNED_INT, 0);
        }
    }
}
