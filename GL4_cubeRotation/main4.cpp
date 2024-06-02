#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float rotationAngle = 0.0f;

// matching viewport size to window size
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

// detects if the Escape key is pressed and closes the application window if so
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void renderCube() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0f, 1.0f, 1.0f);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glLoadIdentity();

  glRotatef(rotationAngle, 1.0f, 0.0f, 1.0f);

  glBegin(GL_QUADS);

  float size = 0.5f;

  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(size, 0.0f, 0.0f);
  glVertex3f(size, size, 0.0f);
  glVertex3f(0.0f, size, 0.0f);

  glVertex3f(0.0f, 0.0f, -size);
  glVertex3f(size, 0.0f, -size);
  glVertex3f(size, size, -size);
  glVertex3f(0.0f, size, -size);

  glEnd();

  glBegin(GL_LINES);

  glVertex3f(0.0f, size, 0.0f);
  glVertex3f(0.0f, size, -size);

  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, -size);

  glVertex3f(size, 0.0f, 0.0f);
  glVertex3f(size, 0.0f, -size);

  glVertex3f(size, size, 0.0f);
  glVertex3f(size, size, -size);

  glEnd();
}

int main() {
  if (!glfwInit()) {
    cerr << "Failed to initialize GLFW" << endl;
    return -1;
  }

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Manual Cube", NULL, NULL);
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

  while (!glfwWindowShouldClose(window)) {
    // handling user inputs
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    renderCube();

    // swaping front ( current ) buffer and back ( in queue ) buffer
    glfwSwapBuffers(window);
    glfwPollEvents();

    rotationAngle += 0.1f;
    if (rotationAngle > 360.0f) {
      rotationAngle -= 360.0f;
    }
  }

  glfwTerminate();
  return 0;
}
