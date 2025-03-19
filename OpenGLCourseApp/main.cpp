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

int main()
{
	// 1. Initalize GLFW

	if ( !glfwInit() )
	{
		printf("GLFW Initialization failed!");
		glfwTerminate();
		return 1;
	}

	// set up GLFW window properties
	// Opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// core proFile has no backwards compatibility, don't want to use old OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Creates a window and its associated OpenGL or OpenGL ES context.
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window",NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW failed to create window!");
		glfwTerminate();
		return 1;
	}

	// 2. Get OpenGL ready
	// Get the buffer size of our created window's information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight); 
	// Set the context for GLEW to use (Choose the 'mainWindow' for OpenGL target)
	glfwMakeContextCurrent(mainWindow);
	
	
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialization failed!");

		//need to Destroy the created window
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	
	
	//set up viewport size for OpenGL to draw in
	glViewport(0, 0, bufferWidth, bufferHeight);


	//loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		//get + handle user input events
		glfwPollEvents();

		//set clear window red
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); //Clear window to red

		//swap the front and back buffers, show the rendered result
		glfwSwapBuffers(mainWindow);
	}

	return 0;
}