#include <iostream>
#include <cmath>
#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include "shaderHandler.h"


float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
};

unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
}

GLFWwindow* initWindow(const char* windowTitle, int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);

    if(window == nullptr) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

bool checkGlad() {
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

int main() {
    mat4 proj = perspective(radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);


    mrn::Polygon cube_data;

    mrn::Vertex ldf;
    ldf.pos = vec3(-0.5, -0.5, -0.5);
    ldf.rgb =  vec3(0.0, 0.0, 0.0);

    mrn::Vertex luf;
    luf.pos = vec3(-0.5, 0.5, -0.5);
    luf.rgb = vec3(0.0, 0.0, 1.0);

    mrn::Vertex rdf;
    rdf.pos = vec3(0.5, -0.5, -0.5);
    rdf.rgb = vec3(0.0, 1.0, 0.0);

    mrn::Vertex ruf;
    ruf.pos = vec3(0.5, 0.5, -0.5);
    ruf.rgb = vec3(0.0, 1.0, 1.0);

    mrn::Vertex ldb;
    ldb.pos = vec3(-0.5, -0.5, 0.5);
    ldb.rgb = vec3(1.0, 0.0, 0.0);

    mrn::Vertex lub;
    lub.pos = vec3(-0.5, 0.5, 0.5);
    lub.rgb = vec3(1.0, 0.0, 1.0);

    mrn::Vertex rdb;
    rdb.pos = vec3(0.5, -0.5, 0.5);
    rdb.rgb = vec3(1.0, 1.0, 0.0);

    mrn::Vertex rub;
    rub.pos = vec3(0.5, 0.5, 0.5);
    rub.rgb = vec3(1.0, 1.0, 1.0);

    cube_data.addVertex(ldf);
    cube_data.addVertex(luf);
    cube_data.addVertex(rdf);
    cube_data.addVertex(ruf);
    cube_data.addVertex(ldb);
    cube_data.addVertex(lub);
    cube_data.addVertex(rdb);
    cube_data.addVertex(rub);

    // Front
    cube_data.addTriangleIndices(0, 1, 2);
    cube_data.addTriangleIndices(1, 2, 3);
    // Left
    cube_data.addTriangleIndices(0, 2, 4);
    cube_data.addTriangleIndices(2, 4, 6);
    // Right
    cube_data.addTriangleIndices(1, 3, 5);
    cube_data.addTriangleIndices(3, 5, 7);
    // Down
    cube_data.addTriangleIndices(0, 1, 4);
    cube_data.addTriangleIndices(1, 4, 5);
    // Up
    cube_data.addTriangleIndices(2, 3, 6);
    cube_data.addTriangleIndices(3, 6, 7);
    // Back
    cube_data.addTriangleIndices(4, 5, 6);
    cube_data.addTriangleIndices(5, 6, 7);


    GLFWwindow* window = initWindow("OpenGL-Sandbox", 800, 600);
    if(!checkGlad()) return -1;

    glViewport(0,0, 800, 600);
    glPointSize(5);
    glEnable(GL_DEPTH_TEST);

    GLuint cube_vertex_arrayinfo;
    GLuint cube_index_buffer;
    glGenVertexArrays(1, &cube_vertex_arrayinfo);
    glGenBuffers(1, &cube_index_buffer);

    glBindVertexArray(cube_vertex_arrayinfo);
    cube_data.initBuf();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    mrn::Shader* cube_shader = new mrn::Shader("shader/rotate.vert", "shader/default.frag");

    mrn::Model c1 = mrn::Model();
    c1.data = &cube_data;
    c1.shader = cube_shader;

    mrn::Model c2 = mrn::Model();
    c2.data = &cube_data;
    c2.shader = cube_shader;


    GLint proj_loc = glGetUniformLocation(cube_shader->id, "projection");
    cube_shader->use();

    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, value_ptr(proj));

    while(!glfwWindowShouldClose(window)) {
        // input
          // -----
        processInput(window);
        // render
        // ------

        clear();

        c1.translate(vec3(3.0f, 3.f, -10.f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        c2.translate(vec3(-1.0f, -1.5f, -6.f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        // glfw: poll events & swap buffers
        // --------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void clear() {
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}