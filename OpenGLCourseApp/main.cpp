// Include standard libraries and OpenGL libraries
#include <stdio.h>
#include <string.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

// Define Window Size and Global Variables
const GLint WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;

//Vertex Specification: Creating a triangle
void CreateTriangle()
{
	// 0.Define 3 vertices for a triangle
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f, // Vertex 1 (X, Y, Z(depth))
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// 1. Generate VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// 2. Bind the VAO (activate it to store configurations)
	glBindVertexArray(VAO);
	
	// 3. Generate VBO (Vertex Buffer Object)
	glGenBuffers(1, &VBO);
	// 4. Bind the VBO (activate it to store configurations)
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	// 5. Attach the vertex data to that VBO.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 6. Define the Attribute Pointer formatting (Passing to shader with location 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);	
	// 7. Enable the Attribute Pointer (Allow passing)
	glEnableVertexAttribArray(0);

	// 8. Unbind the VAO and VBO, ready for the next object to be bound.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
