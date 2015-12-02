#include "gl.h"

#include <iostream>

GL::GL(int major, int minor, int profile) {
  // Initialize GL
  glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac OS X
#endif
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Initialize window
  _window = window();

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
  std::cerr << 7;
    throw glew_exception{};
  }
}

GL::~GL() {
  glfwTerminate();
}

void GL::setKeyCallback(keyCallback cb) {
    glfwSetKeyCallback(_window, cb);
}

void GL::loop(std::function<void()> process) {
  while(!glfwWindowShouldClose(_window)) {
    glfwPollEvents();
    process();
    glfwSwapBuffers(_window);
  }
}

GLFWwindow* GL::window(GLuint width, GLuint height, std::string title) {
  // Make a window
  GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    throw window_exception{};
  }
  glfwMakeContextCurrent(window);
  glViewport(0, 0, width, height);

  return window;
}
