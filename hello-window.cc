#include <iostream>

#include "gl.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
  try {
    GL gl {};

    gl.setKeyCallback(keyCallback);

    gl.loop([] {
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
    });
  } catch (GL::gl_exception& e) {
    std::cerr << e.what();
    return -1;
  }

	return 0;
}

void keyCallback(GLFWwindow* window, int key, int, int action, int) {
	// Close window on ESC
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
