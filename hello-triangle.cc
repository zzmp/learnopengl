#include <iostream>

#include "gl.h"

const GLchar* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
)";

const GLchar* greenFragmentShaderSource = R"(
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

const GLchar* yellowFragmentShaderSource = R"(
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
)";

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
  try {
    GL gl {};

    gl.setKeyCallback(keyCallback);

		// Dynamically compile the shaders
		GLint success;
		GLchar infoLog[512];

		// Dynamically compile vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			return -1;
		}

		// Dynamically compile fragment shaders
		GLuint greenFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(greenFragmentShader, 1, &greenFragmentShaderSource, nullptr);
		glCompileShader(greenFragmentShader);

		glGetShaderiv(greenFragmentShader, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(greenFragmentShader, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::GFRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			return -1;
		}

    GLuint yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, nullptr);
		glCompileShader(yellowFragmentShader);

		glGetShaderiv(yellowFragmentShader, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(yellowFragmentShader, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::YFRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			return -1;
		}

		// Create shader programs
		GLuint greenShaderProgram = glCreateProgram();
		glAttachShader(greenShaderProgram, vertexShader);
		glAttachShader(greenShaderProgram, greenFragmentShader);
		glLinkProgram(greenShaderProgram);

		glGetProgramiv(greenShaderProgram, GL_LINK_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(greenShaderProgram, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::GPROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			return -1;
		}

    GLuint yellowShaderProgram = glCreateProgram();
		glAttachShader(yellowShaderProgram, vertexShader);
		glAttachShader(yellowShaderProgram, yellowFragmentShader);
		glLinkProgram(yellowShaderProgram);

		glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(yellowShaderProgram, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::YPROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			return -1;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(greenFragmentShader);
		glDeleteShader(yellowFragmentShader);

		GLfloat lVertices[] = {
      -0.5f,  0.5f, 0.0f,
      -1.0f, -0.5f, 0.0f,
       0.0f, -0.5f, 0.0f
    };
    GLfloat rVertices[] = {
       0.5f,  0.5f, 0.0f,
       0.0f, -0.5f, 0.0f,
       1.0f, -0.5f, 0.0f
		};

    // Left triangle
		GLuint lVAO;
		glGenVertexArrays(1, &lVAO);
		glBindVertexArray(lVAO);

		GLuint lVBO;
		glGenBuffers(1, &lVBO);
		glBindBuffer(GL_ARRAY_BUFFER, lVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lVertices), lVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

    // Right triangle
    GLuint rVAO;
		glGenVertexArrays(1, &rVAO);
		glBindVertexArray(rVAO);

		GLuint rVBO;
		glGenBuffers(1, &rVBO);
		glBindBuffer(GL_ARRAY_BUFFER, rVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rVertices), rVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    gl.loop([greenShaderProgram, yellowShaderProgram, lVAO, rVAO] {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			// Draw a triangle
			glBindVertexArray(lVAO);
			glUseProgram(greenShaderProgram);
      glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(rVAO);
			glUseProgram(yellowShaderProgram);
      glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
    });

		// Cleanup
		glDeleteVertexArrays(1, &lVAO);
		glDeleteBuffers(1, &lVBO);
		glDeleteVertexArrays(1, &rVAO);
		glDeleteBuffers(1, &rVBO);
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
