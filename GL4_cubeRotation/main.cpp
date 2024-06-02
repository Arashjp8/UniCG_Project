#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float rotationAngle = 0.0f;

// Callback function to adjust the viewport when the window size changes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

// Function to process input
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// Function to render the quads
void renderQuads() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Set the color to white
  glColor3f(1.0f, 1.0f, 1.0f);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Reset transformations
  glLoadIdentity();

  // Apply rotation
  glRotatef(rotationAngle, 1.0f, 0.0f, 1.0f);

  glBegin(GL_QUADS);

  float size = 0.5f;

  // Front face
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(size, 0.0f, 0.0f);
  glVertex3f(size, size, 0.0f);
  glVertex3f(0.0f, size, 0.0f);

  // Back face
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
  // Initialize GLFW
  if (!glfwInit()) {
    cerr << "Failed to initialize GLFW" << endl;
    return -1;
  }

  // Create a windowed mode window and its OpenGL context
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Manual Cube", NULL, NULL);
  if (!window) {
    cerr << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Set the framebuffer size callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    cerr << "Failed to initialize GLEW" << endl;
    return -1;
  }

  // Main render loop
  while (!glfwWindowShouldClose(window)) {
    // Input
    processInput(window);

    // Render here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    renderQuads();

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    // Update rotation angle for animation
    rotationAngle += 0.5f;
    if (rotationAngle > 360.0f) {
      rotationAngle -= 360.0f;
    }
  }

  glfwTerminate();
  return 0;
}
