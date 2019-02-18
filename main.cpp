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

GLFWwindow* initWindow(const char* windowTitle) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, windowTitle, nullptr, nullptr);

    if(window == nullptr) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    return window;
}

int main() {
    char infoLog[512];

    GLFWwindow* window = initWindow("OpenGL-Sandbox");
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << nrAttributes << std::endl;


    // VAO => Vertex Array Object
    GLuint leftTriangle_vao;
    glGenVertexArrays(1, &leftTriangle_vao);
    glBindVertexArray(leftTriangle_vao);
    // VBO => Vertex Buffer Object
    GLuint leftTriangle;
    glGenBuffers(1, &leftTriangle);
    glBindBuffer(GL_ARRAY_BUFFER, leftTriangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);


    GLuint rightTriangle_vao;
    glGenVertexArrays(1, &rightTriangle_vao);
    glBindVertexArray(rightTriangle_vao);
    GLuint rightTriangle;
    glGenBuffers(1, &rightTriangle);
    glBindBuffer(GL_ARRAY_BUFFER, rightTriangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    // EBO => Element Buffer Object
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /*
     * As of now we stored the vertex data within memory on the graphics card as managed by a vertex buffer object named VBO.
     * Next we want to create a vertex and fragment shader that actually processes this data, so let's start building those.
     *
     */

    Shader* firstTriangle = new Shader("shader/simple.vert", "shader/red.frag");
    Shader* secondTriangle = new Shader("shader/simple.vert", "shader/yellow.frag");


    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

  //      glUseProgram(shaderProgram_red);
        firstTriangle->use();
        glBindVertexArray(leftTriangle_vao);

        float timeValue = glfwGetTime();
        float colorValue = (sin(timeValue) / 2.0f) + 0.5f;
        GLint vertexColorLocation = glGetUniformLocation(firstTriangle->id, "ourColor");
        glUniform4f(vertexColorLocation, 1.0 - colorValue, colorValue, 0.0f, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        secondTriangle->use();
    //    glUseProgram(shaderProgram_yellow);
        glBindVertexArray(rightTriangle_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    //    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}