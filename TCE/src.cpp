#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>

#include "global_functions.h"
#include "shader.h"
#include "player.h"
#include "world.h"
#include "ray.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>

constexpr unsigned int SCR_WIDTH = 1024;
constexpr unsigned int SCR_HEIGHT = 512;
constexpr unsigned int PRECISION = 60;
const float RAYS = SCR_WIDTH / PRECISION;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void processInput(GLFWwindow*);
bool isWall();
void castAllRays();
float toRadian(float);

Player* player = new Player(glm::vec2(300.f, 300.f), toRadian(-90), toRadian(60));
World* world = new World(SCR_HEIGHT);
std::vector<Ray*> rays = std::vector<Ray*>();

using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;
using Duration = std::chrono::duration<float, std::ratio<1, 1>>;

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
        0.f,  0.f, 0.f,
        1.f,  1.f, 0.f
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

    player->newPos.x = cos(player->angle) * 5, player->newPos.y = sin(player->angle) * 5;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    const TimePoint tpStart = Clock::now();
    TimePoint tpLast = tpStart;
    while (!glfwWindowShouldClose(window))
    {
        // ---------------------------------------------------------------------------------------------------------------------------------------------------------
        TimePoint now = Clock::now();
        const float time = std::chrono::duration_cast<Duration>(now - tpStart).count();
        const float dt = std::chrono::duration_cast<Duration>(now - tpLast).count();
        tpLast = now;

        glClear(GL_COLOR_BUFFER_BIT);
        processInput(window);

        // ---------------------------------------------------------------------------------------------------------------------------------------------------------
        glm::mat4 projection = glm::ortho(0.f, 1024.f, 512.f, 0.f);
        shader1.setMat4("projection", projection);
        glm::mat4 model;

        glBindVertexArray(VAO2);
        shader2.use();
        for (int y = 0; y < world->ySize; y++)
        {
            for (int x = 0; x < world->xSize; x++)
            {
                shader2.setMat4("projection", projection);

                model = glm::mat4(1.0f);                                                                                  
                model = glm::translate(model, glm::vec3(((x * world->sizeTile) + (world->sizeTile / 2)), ((y * world->sizeTile) + (world->sizeTile / 2)), 0.f));
                model = glm::scale(model, glm::vec3(world->sizeTile, world->sizeTile, world->sizeTile));
                shader2.setMat4("model", model);

                if (world->map[y][x] > 0)
                    shader2.setBool("wall", true);
                else
                    shader2.setBool("wall", false);
                
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
        }

        // ---------------------------------------------------------------------------------------------------------------------------------------------------------
        shader1.use();
        shader1.setVec4("color", 0.2f, 0.5f, 0.8f, 0.5f);
        glBindVertexArray(VAO3);
        glLineWidth(4);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(player->position, 0.f));
        model = glm::scale(model, glm::vec3(player->newPos.x * 40, player->newPos.y * 40, 0.f));
        shader1.setMat4("model", model);
        glDrawArrays(GL_LINES, 0, 2);

        // ---------------------------------------------------------------------------------------------------------------------------------------------------------
        rays.clear();
        castAllRays();

        shader1.use();
        shader1.setVec4("color", 0.2f, 0.5f, 0.8f, 0.5f);
        for (Ray* r : rays)
        {
            glBindVertexArray(VAO3);
            glLineWidth(4);
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(player->position, 0.f));
            model = glm::scale(model, glm::vec3(cos(r->rayAngle) * 40, sin(r->rayAngle) * 40, 0.f));
            shader1.setMat4("model", model);
            glDrawArrays(GL_LINES, 0, 2);
        }

        // ---------------------------------------------------------------------------------------------------------------------------------------------------------
        shader1.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(player->position, 0.f));
        shader1.setMat4("model", model);
        shader1.setVec4("color", 0.5f, 0.5f, 0.5f, 1.f);

        glBindVertexArray(VAO1);
        glPointSize(32);
        glDrawArrays(GL_POINTS, 0, 1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteVertexArrays(1, &VAO3);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader1.ID);
    glDeleteProgram(shader2.ID);

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
    if (!isWall())
    {
        if (glfwGetKey(window, GLFW_KEY_S))
        {
            player->position.x -= player->newPos.x;
            player->position.y += player->newPos.y;
        }

        if (glfwGetKey(window, GLFW_KEY_W))
        {
            player->position.x += player->newPos.x;
            player->position.y += player->newPos.y;
        }
    }


    if (glfwGetKey(window, GLFW_KEY_A))
    { 
        player->angle -= 0.1f;

        player->angle = normalizeAngle(player->angle);

        player->newPos.x = cos(player->angle) * player->speed;
        player->newPos.y = sin(player->angle) * player->speed;
    }

    if (glfwGetKey(window, GLFW_KEY_D))
    {
        player->angle += 0.1f;

        player->angle = normalizeAngle(player->angle);

        player->newPos.x = cos(player->angle) * player->speed;
        player->newPos.y = sin(player->angle) * player->speed;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool isWall()
{
    if (player->position.x+player->newPos.x < 0 || player->position.x+player->newPos.x > SCR_WIDTH / 2 || player->position.y+player->newPos.y < 0 || player->position.y+player->newPos.y > SCR_HEIGHT)
        return true;

    return world->map[floor((player->position.y + player->newPos.y) / world->sizeTile)][floor((player->position.x + player->newPos.x) / world->sizeTile)] != 0;  
}

void castAllRays()
{
    unsigned int columnId = 0;

    float rayAngle = player->angle - (player->fov / 2);

    for (unsigned int i = 0; i < 1/*RAYS*/; i++)
    {
        rayAngle += player->fov / RAYS;
        Ray* ray = new Ray(rayAngle);
        rays.push_back(ray);

        columnId++;
    }
}