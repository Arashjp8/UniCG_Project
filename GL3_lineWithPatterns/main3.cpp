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
    glEnable(GL_LINE_STIPPLE);

    glLineStipple(1, 0x00FF);

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.9f, 0.0f);
    glVertex2f(0.9f, 0.0f);
    glEnd();

    glLineStipple(5, 0xFAFA);

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.9f, -0.2f);
    glVertex2f(0.9f, -0.2f);
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}

int main()
{
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Patterned Lines", NULL, NULL);
    if (!window)
    {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (glewInit() != GLEW_OK)
    {
        cerr << "Failed to initialize GLEW" << endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderLines();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
