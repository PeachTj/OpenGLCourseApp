// Include standard libraries and OpenGL libraries
#include <stdio.h>
#include <string.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

// Define Window Size and Global Variables
const GLint WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;

// Vertex Shader code
static const char* vertexShaderSource = "                                                \n\
#version 460                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;											  \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);				  \n\
}";

// Fragment Shader
static const char* fragmentShaderSource = "                                                \n\
#version 460                                                                  \n\
                                                                              \n\
out vec4 colour;                                                              \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);                                        \n\
}";



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
// Create the shader
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	// 1. Create a shader object
	GLuint theShader = glCreateShader(shaderType);
	
	// 2. Attach the shader source code to the shader object
	glShaderSource(theShader, 1, &shaderCode, NULL);
	glCompileShader(theShader);

	int  success;
	char infoLog[1024];
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, infoLog);
		printf("Error compiling shader type %d: '%s'\n", shaderType, infoLog);
		return;

	}
	glAttachShader(theProgram, theShader);

}	

// Compile the shader
void CompileShaders()
{
	// 1. Create a shader program
	shader = glCreateProgram();
	if (!shader)
	{
		printf("Error creating shader program!\n");
		return;
	}

	// Add the shader to the program
	AddShader(shader, vertexShaderSource, GL_VERTEX_SHADER);
	AddShader(shader, fragmentShaderSource, GL_FRAGMENT_SHADER);

	int  success;
	char infoLog[1024];

	// Link the shader program (make it executable)
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		printf("Error linking shader program: '%s'\n", infoLog);
		return;
	}

	// Validate the program (optional, but recommended for debugging)
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		printf("Error validating shader program: '%s'\n", infoLog);
		return;
	}
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

	CreateTriangle();
	CompileShaders();

	//loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		//get + handle user input events
		glfwPollEvents();

		//set clear window red
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); //Clear window to red

		// simply using the shader program
		glUseProgram(shader);
		//printf("Shader Program ID: %d\n", shader);
		glBindVertexArray(VAO);
		// draw the object
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(0);

		//swap the front and back buffers, show the rendered result
		glfwSwapBuffers(mainWindow);
	}

	return 0;
}