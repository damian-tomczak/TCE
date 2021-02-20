#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>

#include "shader.h"

#include <iostream>
#include <vector>
#include <math.h>

constexpr double PI = 3.141592653589793238463;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void processInput(GLFWwindow*);

constexpr unsigned int SCR_WIDTH = 1024;
constexpr unsigned int SCR_HEIGHT = 512;

glm::vec2 player = glm::vec2(300, 300);
float pdx, pdy, pa;

unsigned int type = 0;

std::vector<std::vector<unsigned int>> world =
{
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TCE", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices1[] = {     
        0.f, 0.f, 0.f
    };

    float vertices2[] = {
        // first triangle
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f,  0.5f, 0.0f,  // top left 
        // second triangle
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

    float vertices3[] = {
        0.f, -0.5f, 0.f,
        0.f,  0.5f, 0.f
    };

    unsigned int VBO, VAO1, VAO2, VAO3;
    glGenVertexArrays(1, &VAO1);
    glGenVertexArrays(1, &VAO2);
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO2);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO3);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    Shader shader1("shader1.vert", "shader1.frag");
    Shader shader2("shader2.vert", "shader2.frag");

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        processInput(window);

        glm::mat4 projection = glm::ortho(0.f, 1024.f, 512.f, 0.f);
        shader1.setMat4("projection", projection);
        glm::mat4 model;

        float sizeTile = SCR_HEIGHT / world.size();
        glBindVertexArray(VAO2);
        shader2.use();
        for (int y = 0; y < world.size(); y++)
        {
            for (int x = 0; x < world[y].size(); x++)
            {
                shader2.setMat4("projection", projection);

                model = glm::mat4(1.0f);                                                                                  
                model = glm::translate(model, glm::vec3(((x * sizeTile) + (sizeTile / 2)), ((y * sizeTile) + (sizeTile / 2)), 0.f));
                model = glm::scale(model, glm::vec3(sizeTile, sizeTile, sizeTile));
                shader2.setMat4("model", model);

                if (world[x][y] == 1)
                    shader2.setBool("wall", true);
                else
                    shader2.setBool("wall", false);
                
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
        }

        shader1.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(player, 0.f));
        shader1.setMat4("model", model);

        glBindVertexArray(VAO1);
        glPointSize(32);
        glDrawArrays(GL_POINTS, 0, 1);

        glBindVertexArray(VAO3);
        glLineWidth(10);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(player.x+pdx*5, player.y+pdy*5, 0.f));
        shader1.setMat4("model", model);
        glDrawArrays(GL_LINES, 0, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader1.ID);

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (key == GLFW_KEY_X && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_S))
    {
        player.x -= pdx;
        player.y += pdy;
    }

    if (glfwGetKey(window, GLFW_KEY_W))
    {
        player.x += pdx;
        player.y += pdy;
    }

    if (glfwGetKey(window, GLFW_KEY_A))
    {
        pa -= 0.1f;
        if (pa < 0)
            pa += 2 * PI;
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }

    if (glfwGetKey(window, GLFW_KEY_D))
    {
        pa += 0.1f;
        if (pa > 2 * PI)
            pa -= 2 * PI;
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}