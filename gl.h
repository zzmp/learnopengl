#ifndef __GL_GL_H__
#define __GL_GL_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <functional>
#include <string>

constexpr GLuint WIDTH = 800, HEIGHT = 600;

class GL {
  using keyCallback = GLFWkeyfun;
  public:
    GL(int major =3, int minor =3, int profile =GLFW_OPENGL_CORE_PROFILE);
    ~GL();

    // Set a key callback
    // Must be called prior to running a game loop
    void setKeyCallback(keyCallback cb);
    // Run a game loop
    void loop(std::function<void()> process);

    // Exceptions
    class gl_exception : public std::exception {};
    class glew_exception : gl_exception {
      const char* what() const throw() override { return "Failed to initialize GLEW"; }
    };
    class window_exception : gl_exception {
      const char* what() const throw() override { return "Failed to create GLFW window"; }
    };

  private:
    // Make a window
    GLFWwindow* window(GLuint width =WIDTH, GLuint height =HEIGHT, std::string title ="OpenGL Playground");

    GLFWwindow* _window;
};

#endif
