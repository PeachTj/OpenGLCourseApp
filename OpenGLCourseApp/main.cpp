#include <stdio.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

//Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

int main() {

    //initialize GLFW
    
    if (!glfwInit()) 
    {
		printf("GLFW failed to initialize!");
        glfwTerminate();
        return 1;
    }

	//set up GLFW window properties
	//Opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//core proFile has no backwards compatibility, don't want to use old OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	
	//window creation failed£¬mainWindow is NULL
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	//get the buffer size of our created window's information

	/*
	Buffer Objects are OpenGL Objects that store an array of unformatted memory allocated by the OpenGL context (AKA the GPU). 
	These can be used to store vertex data, pixel data retrieved from images or the framebuffer, 
	and a variety of other things.
	*/

	//pass the address of mainwindow, get the buffer size of the window
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//set context For GLEW to use
	// use glew to set up OpenGL functions, need to tie to the window
	glfwMakeContextCurrent(mainWindow);

	//allow modern extension features
	glewExperimental = GL_TRUE;

	//initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialization failed!");
		
		//need to Destroy the created window
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	//set up viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	//loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		//get + handle user input events
		glfwPollEvents();

		//clear window
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//Just clear the color buffer
		
		//swap the front and back buffers, show the rendered result
		glfwSwapBuffers(mainWindow);
	}

    return 0;
}