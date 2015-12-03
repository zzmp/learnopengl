#include <cmath>
#include <iostream>

#include "gl.h"

const std::string vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(position, 1.0);
    ourColor = color;
}
)";

const std::string fragmentShaderSource = R"(
#version 330 core

in vec3 ourColor;
out vec4 color;

void main()
{
    color = vec4(ourColor, 1.0f);
}
)";

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
  try {
    GL gl {};

    gl.setKeyCallback(keyCallback);

    Shader vertexShader {vertexShaderSource, GL_VERTEX_SHADER};
    Shader fragmentShader {fragmentShaderSource, GL_FRAGMENT_SHADER};

    Program program {};
    program.attach(vertexShader);
    program.attach(fragmentShader);
    program.link();

		GLfloat vertices[] = {
      // Positions        Colors
       0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
       0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

		GLuint VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

    // Colors
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

    gl.loop([&program, VAO] {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw a triangle
			glBindVertexArray(VAO);
      program.use();
      glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
    });

		// Cleanup
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
  } catch (gl_exception const& e) {
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
