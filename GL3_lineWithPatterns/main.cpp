#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void renderLines()
{
    // Enable line stipple
    glEnable(GL_LINE_STIPPLE);

    // Define the pattern and factor
    glLineStipple(1, 0x00FF); // Factor of 1, pattern 0x00FF (dash-dot pattern)

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f); // Red color
    glVertex2f(-0.9f, 0.0f);
    glVertex2f(0.9f, 0.0f);
    glEnd();

    // Change the pattern and factor
    glLineStipple(3, 0xAAAA); // Factor of 3, pattern 0xAAAA (alternating dots and dashes)

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f); // Blue color
    glVertex2f(-0.9f, -0.2f);
    glVertex2f(0.9f, -0.2f);
    glEnd();

    // Disable line stipple
    glDisable(GL_LINE_STIPPLE);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Patterned Lines", NULL, NULL);
    if (!window)
    {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set the framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        cerr << "Failed to initialize GLEW" << endl;
        return -1;
    }

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the patterned lines
        renderLines();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
