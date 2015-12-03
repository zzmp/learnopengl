#ifndef __GL_GL_H__
#define __GL_GL_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <functional>
#include <string>

constexpr GLuint WIDTH = 800, HEIGHT = 600;

// Exceptions
class gl_exception : public std::exception {};

class GL {
  using keyCallback = GLFWkeyfun;
  public:
    GL(int major =3, int minor =3, int profile =GLFW_OPENGL_CORE_PROFILE);
    ~GL();

    class glew_exception : public gl_exception {
      const char* what() const throw() override { return "Failed to initialize GLEW"; }
    };
    class window_exception : public gl_exception {
      const char* what() const throw() override { return "Failed to create GLFW window"; }
    };

    // Set a key callback
    // Must be called prior to running a game loop
    void setKeyCallback(keyCallback cb);

    // Run a game loop
    void loop(std::function<void()> process);

  private:
    // Make a window
    GLFWwindow* window(GLuint width =WIDTH, GLuint height =HEIGHT, std::string title ="OpenGL Playground");

    GLFWwindow* _window;
};

class Shader;

class Program {
  public:
    Program();

    class link_exception : public gl_exception {
      const char* what() const throw() override { return _what.c_str(); }
      public:
        link_exception(std::string info) :_what{"Failed to link: " + info} {}
      private:
        std::string _what;
    };

    void attach(Shader shader);
    void link();
    void use();

    GLint getUniform(std::string uniform);

  private:
    GLuint _program;
};

class Shader {
  public:
    Shader(std::string source, int type =GL_VERTEX_SHADER);
    ~Shader();

    class compile_exception : public gl_exception {
      const char* what() const throw() override { return _what.c_str(); }
      public:
        compile_exception(std::string info) :_what{"Failed to compile: " + info} {}
      private:
        std::string _what;
    };

  protected:
    friend void Program::attach(Shader shader);
    GLuint _shader;
};

#endif
