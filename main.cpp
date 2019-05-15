#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <glfw3.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/* ---- GLM ---- */
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

/* ---- own header ---- */
#include "mrn/Shader.h"
#include "mrn/Mesh.h"
#include "mrn/Model.h"
#include "mrn/camera/Camera.h"
#include "mrn/Scene.h"
#include "mrn/Primitives.h"
#include "mrn/FontRenderer.h"




void clear();
using namespace glm;

int loadTexture() {
    // Texture Loading
    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/wall.jpg", &width, &height, &nrChannels, 0);
    if(data == nullptr) std::cout << "bla" << std::endl;
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    return texture;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, mrn::Scene* scene) {
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

    // camera control

    if(glfwGetKey(window, GLFW_KEY_W)) {
        vec3 camPos = scene->cam.getPos();
        camPos.z = camPos.z - 0.1f;
        scene->cam.setPos(camPos);
    }

    if(glfwGetKey(window, GLFW_KEY_A)) {
        vec3 camPos = scene->cam.getPos();
        camPos.x = camPos.x - 0.1f;
        scene->cam.setPos(camPos);
    }

    if(glfwGetKey(window, GLFW_KEY_S)) {
        vec3 camPos = scene->cam.getPos();
        camPos.z = camPos.z + 0.1f;
        scene->cam.setPos(camPos);
    }

    if(glfwGetKey(window, GLFW_KEY_D)) {
        vec3 camPos = scene->cam.getPos();
        camPos.x = camPos.x + 0.1f;
        scene->cam.setPos(camPos);
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


    mrn::Mesh* cube_data = mrn::Primitive::createCube();
    mrn::Mesh* pyramid_data = mrn::Primitive::createPyramid();


    GLFWwindow* window = initWindow("OpenGL-Sandbox", 800, 600);
    if(!checkGlad()) return -1;

    glViewport(0,0, 800, 600);
    glPointSize(5);
    glEnable(GL_DEPTH_TEST);


    cube_data->initBuf();
    pyramid_data->initBuf();


    mrn::Shader* default_shader = new mrn::Shader("shader/rotate.vert", "shader/default.frag");

    mrn::Model c1 = mrn::Model();
    c1.mesh = cube_data;
    c1.mesh->initBuf();
    c1.translate(0.0f, 0.f, -5.f);

    mrn::Model c2 = mrn::Model();
    c2.mesh = cube_data;
    c2.mesh->initBuf();
    c2.translate(-1.0f, -1.5f, -6.f);

    mrn::Model c3 = mrn::Model();
    c3.mesh = pyramid_data;
    c3.mesh->initBuf();
    c3.translate(1.0f, 1.0f, -8.0f);


    c1.attachShader(default_shader);
    c2.attachShader(default_shader);
    c3.attachShader(default_shader);

    mrn::Scene scene = mrn::Scene();
    // ------------
    // camera setup
    // ------------
    scene.cam.setFov(45.0f);
    scene.objects.push_back(c1);
    scene.objects.push_back(c2);
    scene.objects.push_back(c3);

    GLint proj_loc = glGetUniformLocation(default_shader->id, "projection");
    default_shader->use();
    mrn::FontRenderer* fr = new mrn::FontRenderer();
    fr->setFont("fonts/arial.ttf");
    fr->setFontSize(16);
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, value_ptr(proj));
    while(!glfwWindowShouldClose(window)) {
        clear();


        processInput(window, &scene);

        fr->renderText("Blablabla", 0, 0, vec3(1, 0, 0));
        scene.render();
        // glfw: poll events & swap buffers
        // --------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void clear() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}