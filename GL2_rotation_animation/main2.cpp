#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void rotate(float &x, float &y, float angle) {
  float s = sin(angle);
  float c = cos(angle);

  float xnew = x * c - y * s;
  float ynew = x * s + y * c;

  x = xnew;
  y = ynew;
}

// matching viewport size to window size
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

// detects if the Escape key is pressed and closes the application window if so
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  if (!glfwInit()) {
    cerr << "Failed to initialize GLFW" << endl;
    return -1;
  }

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (!window) {
    cerr << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // lessons for window resize events
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (glewInit() != GLEW_OK) {
    cerr << "Failed to initialize GLEW" << endl;
    return -1;
  }

  float angle = 0.0f;
  // float angle = 0.5f;

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[8] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};

    for (int i = 0; i < 8; i += 2) {
      rotate(vertices[i], vertices[i + 1], angle);
    }

    glBegin(GL_QUADS);
    for (int i = 0; i < 8; i += 2) {
      glVertex2f(vertices[i], vertices[i + 1]);
    }
    glEnd();

    // angle += 0.01f;

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
