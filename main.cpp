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
    int screenWidth = 800;
    int screenHeight = 600;
    char infoLog[512];

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
 //   trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));


    glm::mat4 ortho = glm::ortho(0.0f, 800.f, 0.0f, 600.0f, 0.1f, 100.f);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

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


    // Texture Loading
    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/wall.jpg", &width, &height, &nrChannels, 0);
    if(data == nullptr) std::cout << "bla" << std::endl;
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);




    // VAO => Vertex Array Object
    GLuint leftTriangle_vao;
    glGenVertexArrays(1, &leftTriangle_vao);
    glBindVertexArray(leftTriangle_vao);
    // VBO => Vertex Buffer Object
    GLuint leftTriangle_vbo;
    glGenBuffers(1, &leftTriangle_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, leftTriangle_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);


    GLuint rightTriangle_vao;
    glGenVertexArrays(1, &rightTriangle_vao);
    glBindVertexArray(rightTriangle_vao);
    GLuint rightTriangle_vbo;
    glGenBuffers(1, &rightTriangle_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, rightTriangle_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint upperTriangle_vao;
    glGenVertexArrays(1, &upperTriangle_vao);
    glBindVertexArray(upperTriangle_vao);
    GLuint upperTriangle_vbo;
    glGenBuffers(1, &upperTriangle_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, upperTriangle_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(thirdTriangle), thirdTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // cube
    GLuint cube_vao;
    glGenVertexArrays(1, &cube_vao);
    glBindVertexArray(cube_vao);
    GLuint cube_vbo;
    glGenBuffers(1, &cube_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
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

    Shader* firstTriangle = new Shader("shader/simple.vert", "shader/uniformColor.frag");
    Shader* secondTriangle = new Shader("shader/simple.vert", "shader/inputColor.frag");
    Shader* thirdTriangle = new Shader("shader/texture.vert", "shader/texture.frag");

    Shader* cube = new Shader("shader/texture.vert", "shader/texture.frag");

    cube->use();
//    GLint vertexOffsetLocation = glGetUniformLocation(cube->id, "offset");
    GLint modelLocation = glGetUniformLocation(cube->id, "model");
    GLint viewLocation = glGetUniformLocation(cube->id, "view");
    GLint projectionLocation = glGetUniformLocation(cube->id, "projection");


 //   glBindTexture
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        firstTriangle->use();
//        glBindVertexArray(leftTriangle_vao);

//
//
//        float timeValue = glfwGetTime();
//        float colorValue = (sin(timeValue) / 2.0f) + 0.5f;
//        GLint vertexColorLocation = glGetUniformLocation(firstTriangle->id, "ourColor");
//        glUniform4f(vertexColorLocation, 1.0 - colorValue, colorValue, 1.0 - colorValue, 1.0f);
//
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        secondTriangle->use();
//        glBindVertexArray(rightTriangle_vao);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//    //    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        thirdTriangle->use();
//
//
//        glBindVertexArray(upperTriangle_vao);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        float rot = (float)glfwGetTime();
        model = glm::mat4(1.0f);
        model = glm::rotate(model, rot, glm::vec3(0.1f, 0.3f, 0.5f));
        cube->use();
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(cube_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}