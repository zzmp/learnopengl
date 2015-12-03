#include <iostream>

#include "gl.h"

const std::string vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
)";

const std::string greenFragmentShaderSource = R"(
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

const std::string yellowFragmentShaderSource = R"(
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

    Shader vertexShader {vertexShaderSource, GL_VERTEX_SHADER};
    Shader greenShader {greenFragmentShaderSource, GL_FRAGMENT_SHADER};
    Shader yellowShader {yellowFragmentShaderSource, GL_FRAGMENT_SHADER};

    Program greenProgram {};
    greenProgram.attach(vertexShader);
    greenProgram.attach(greenShader);
    greenProgram.link();

    Program yellowProgram {};
    yellowProgram.attach(vertexShader);
    yellowProgram.attach(yellowShader);
    yellowProgram.link();

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

    gl.loop([&greenProgram, &yellowProgram, lVAO, rVAO] {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw a triangle
			glBindVertexArray(lVAO);
      greenProgram.use();
      glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(rVAO);
      yellowProgram.use();
      glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
    });

		// Cleanup
		glDeleteVertexArrays(1, &lVAO);
		glDeleteBuffers(1, &lVBO);
		glDeleteVertexArrays(1, &rVAO);
		glDeleteBuffers(1, &rVBO);
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
