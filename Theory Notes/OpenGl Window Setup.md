- # OpenGL Window Set up

  ## 📌 What this code does

  ### 🎯 Big Picture

  This code does 3 important things:

  1. **Opens a window** (like opening a blank canvas on your screen).
  2. **Get OpenGL ready** --Choose and prepare the correct GPU memory (context)
  3. **Keeps clearing the screen with RED color** again and again, until you close the window.

  ## 🚩 Section 1: Get OpenGL ready --Choose and prepare the correct GPU memory (context)Start GLFW (the window system)

  - Tell GLFW what kind of OpenGL window we want
  - Create the window

  ```c++
  	// Initalize GLFW
  
  	if ( !glfwInit() )
  	{
  		printf("GLFW Initialization failed!");
  		glfwTerminate();
  		return 1;
  	}
  
  	//set up GLFW window properties
  	//Opengl version
  	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  	//core proFile has no backwards compatibility, don't want to use old OpenGL
  	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  	//Allow forward compatibility
  	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  	//creates a window and its associated OpenGL or OpenGL ES context.
  	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window",NULL, NULL);
  	if (!mainWindow)
  	{
  		printf("GLFW failed to create window!");
  		glfwTerminate();
  		return 1;
  	}
  ```

  - [`glfwInit()`](https://www.glfw.org/docs/latest/group__init.html#gaacd99a68e6e1caf58a35ef6f9080d395) - Initialize the GLFW library.
  - [`glfwWindowHint()`](https://www.glfw.org/docs/latest/group__window.html#ga8551ecd62a728dfc84e635d728d78479) - Set window and context properties (e.g., OpenGL version).
  - [`glfwCreateWindow()`](https://www.glfw.org/docs/latest/group__window.html#ga0e2637a4161afb283f5300bad10c5a5a) - Creates a window and its associated OpenGL or OpenGL ES context.

  ## 🚩 Section 2: Get OpenGL ready --Choose and prepare the correct GPU memory (context)

  - Ask for the framebuffer size
  - Make the window the current OpenGL target
  - Start GLEW to load OpenGL functions
  - Set up the viewport

  ```c++
  int bufferWidth, bufferHeight;
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
  glfwMakeContextCurrent(mainWindow);
  glewExperimental = GL_TRUE;
  glewInit();
  glViewport(0, 0, bufferWidth, bufferHeight);
  ```

  ```
  GPU MEMORY:
  -----------------------------------
  | CONTEXT for window1             |
  | - shaders                       |
  | - VAOs / VBOs                   |
  | - framebuffer (pixel area)      |
  -----------------------------------
  | CONTEXT for window2             |
  | - shaders (can be different)    |
  | - other VAOs / VBOs             |
  | - another framebuffer           |
  -----------------------------------
  
  glfwMakeContextCurrent() switches between these two blocks.
  Buffer size: While the size of a window is measured in screen coordinates, OpenGL works with pixels
  ```

  - [`glfwGetFramebufferSize()`](https://www.glfw.org/docs/latest/group__window.html#gafb827800eedbfcbc97b1e5408df668d7) - Get actual pixel size of framebuffer.
  - [`glfwMakeContextCurrent()`](https://www.glfw.org/docs/latest/group__context.html#ga68e68b2110277c1455f794471a575ebf) - Set the current OpenGL context for rendering.
  - [`glewExperimental`](http://glew.sourceforge.net/basic.html) -  can be turned on by setting it to GL_TRUE before calling `glewInit()`, which ensures that all extensions with valid entry points will be exposed.
  - [`glewInit()`](http://glew.sourceforge.net/basic.html) - Initialize GLEW (load OpenGL function pointers).
  - [`glViewport()`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glViewport.xhtml) - Define the rendering area(OpenGL drawing area) inside the window.

  

  ## 🚩 Section 3: Clear screen to RED in a loop

  - Keep checking for user input
  - Set the background color to red
  - Clear the screen
  - Show the cleared (red) screen

  ```c++
  
  while (!glfwWindowShouldClose(mainWindow)) {
      glfwPollEvents();
      glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(mainWindow);
  }
  ```

  ## 📝 Notes

  - **GLFW** = handles window + input.
  - **GLEW** = loads OpenGL functions.
  - **OpenGL** = draws your content (in this case, clears the window with red).

- [`glfwWindowShouldClose()`](https://www.glfw.org/docs/latest/group__window.html#ga3f4f9ae7749bc0983b91dd2f274c1d36) - Check if the user has requested to close the window.
- [`glfwPollEvents()`](https://www.glfw.org/docs/latest/group__window.html#ga6e042d05823c11e11c2b0e03b0d3b6c3) - Poll for user input or window events.
- [`glClearColor()`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClearColor.xhtml) - Set the color to clear the screen with.
- [`glClear()`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClear.xhtml) - Clear the color buffer (apply `glClearColor`).
- [`glfwSwapBuffers()`](https://www.glfw.org/docs/latest/group__window.html#ga33278ba42d7547c394a63bcfa6e6b1f4) - Swap the front and back buffers (double buffering).