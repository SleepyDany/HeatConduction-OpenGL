#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGL/ShaderClass.h"
#include "OpenGL/VBO.h"
#include "OpenGL/VAO.h"
#include "OpenGL/EBO.h"

int main()
{
    // Initialize GLFW
    glfwInit();

    // What version of OpenGL GLFW should use (OpenGL 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // CORE profile (only have the modern functions)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(720, 720, "Heat Conduction", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return -1;
    }

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);
    
    // Load GLAD so it configures OpenGL
    gladLoadGL();

    // Specify the viewport of OpenGL in the window (from x,y to x1,y1)
    glViewport(0, 0, 720, 720);

    // Creates shader object using shaders default.vert and default.frag
    Shader shader_program("Resources/default.vert", "Resources/default.frag");

    GLuint uColorID = glGetUniformLocation(shader_program.ID, "uColor");

    // Tell OpenGL which Shader Program we want to use
    shader_program.Activate();
    double last_time = glfwGetTime();
    double cur_time = last_time;

    while (!glfwWindowShouldClose(window))
    {
        cur_time = glfwGetTime();
        if (cur_time - last_time <= 1.0 / 60)
            continue;
        else
        {
            last_time = cur_time;
        }

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

         glfwSwapBuffers(window);

        // All GLFW Events
        glfwPollEvents();
    }

    shader_program.Delete();

    // Delete window
    glfwDestroyWindow(window);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}