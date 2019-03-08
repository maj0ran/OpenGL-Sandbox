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
  //  trans = scale(trans, vec3(0.1, 0.5, 0.5));

    mrn::Triangle triangle_data = mrn::Triangle();

    triangle_data.up.pos = vec3(0.0, 0.5, 0.0);
    triangle_data.up.rgb = vec3(1.0, 0.0, 0.0);

    triangle_data.left.pos = vec3(-0.5, -0.5, 0.0);
    triangle_data.left.rgb = vec3(0.0, 1.0, 0.0);

    triangle_data.right.pos = vec3(0.5, -0.5, 0.0);
    triangle_data.right.rgb = vec3(0.0, 0.0, 1.0);

    mrn::Cube cube_data = mrn::Cube();

    cube_data.leftDownFront.pos = vec3(-0.5, -0.5, -0.5);
    cube_data.leftDownFront.rgb = vec3(0.0, 0.0, 0.0);

    cube_data.leftUpFront.pos = vec3(-0.5, 0.5, -0.5);
    cube_data.leftUpFront.rgb = vec3(0.0, 0.0, 1.0);

    cube_data.rightDownFront.pos = vec3(0.5, -0.5, -0.5);
    cube_data.rightDownFront.rgb = vec3(0.0, 1.0, 0.0);

    cube_data.rightUpFront.pos = vec3(0.5, 0.5, -0.5);
    cube_data.rightUpFront.rgb = vec3(0.0, 1.0, 1.0);

    cube_data.leftDownBack.pos = vec3(-0.5, -0.5, 0.5);
    cube_data.leftDownBack.rgb = vec3(1.0, 0.0, 0.0);

    cube_data.leftUpBack.pos = vec3(-0.5, 0.5, 0.5);
    cube_data.leftUpBack.rgb = vec3(1.0, 0.0, 1.0);

    cube_data.rightDownBack.pos = vec3(0.5, -0.5, 0.5);
    cube_data.rightDownBack.rgb = vec3(1.0, 1.0, 0.0);

    cube_data.rightUpBack.pos = vec3(0.5, 0.5, 0.5);
    cube_data.rightUpBack.rgb = vec3(1.0, 1.0, 1.0);

    GLFWwindow* window = initWindow("OpenGL-Sandbox", 800, 600);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!checkGlad()) return -1;
    glViewport(0,0, 800, 600);


    GLuint triangle_vertex_info;
    GLuint triangle_data_buffer;
    glGenVertexArrays(1, &triangle_vertex_info);
    glGenBuffers(1, &triangle_data_buffer);

    glBindVertexArray(triangle_vertex_info);

    glBindBuffer(GL_ARRAY_BUFFER, triangle_data_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), &triangle_data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)( 3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    GLuint cube_vertex_arrayinfo;
    GLuint cube_vertex_buffer;
    GLuint cube_index_buffer;
    glGenVertexArrays(1, &cube_vertex_arrayinfo);
    glGenBuffers(1, &cube_vertex_buffer);
    glGenBuffers(1, &cube_index_buffer);

    glBindVertexArray(cube_vertex_arrayinfo);

    glBindBuffer(GL_ARRAY_BUFFER, cube_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_data), &cube_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mrn::cube_indices), mrn::cube_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    mrn::Shader* triangle = new mrn::Shader("shader/default.vert", "shader/default.frag");
    mrn::Shader* cube = new mrn::Shader("shader/rotate.vert", "shader/default.frag");

    GLint transform_loc = glGetUniformLocation(cube->id, "transform");
    GLint proj_loc = glGetUniformLocation(cube->id, "proj");
    cube->use();

    //glPointSize(10);
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window)) {
        // transformations
        // ---------------
        mat4 trans = mat4(1.0f);
        trans = translate(trans, vec3(0.0f, 0.f, -3.f));
        trans = rotate(trans, float(glfwGetTime()), vec3(0.8, .5, 0.3));
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, value_ptr(trans));
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, value_ptr(proj));
        // input
        // -----
        processInput(window);
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube->use();
        glBindVertexArray(cube_vertex_arrayinfo);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        // glfw: poll events & swap buffers
        // --------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}