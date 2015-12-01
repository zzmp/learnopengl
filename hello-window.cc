#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

constexpr GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
  // Initialize GL
  glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac OS X
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Make a window
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glViewport(0, 0, WIDTH, HEIGHT);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // Game loop
  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
  }

  // Cleanup
  glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// Close window on ESC
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
