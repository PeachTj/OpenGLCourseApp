- # Shaders and the Rendering Pipeline

  ## 📌 The Rendering Pipeline Stages

  1. **Vertex Specification**
  2. **Vertex Shader *(programmable)***
  3. **Tessellation *(programmable)***
  4. **Geometry Shader *(programmable)***
  5. **Vertex Post-Processing**
  6. **Primitive Assembly**
  7. **Rasterization**
  8. **Fragment Shader *(programmable)***
  9. **Per-Sample Operations**

  ### 📖  Overview  of programmable stages

  - ✅ Section 1: **Vertex Specification**
  - ✅ Section 2: **Vertex Shader and Fragment Shader** 
  - ✅ Section 3: **Shader program**
  - ✅ Section 4: **main loop**
  
  ## 🚩 Vertex Specification
  
  ### 🔸 Create a triangle 
  
  #### 📍 Core Concepts
  
  - **Definition**: 
    - Vertex Specification is the process of clearly describing to OpenGL **what shape to draw** (I draw a triangle), **where the points are stored**, and **how data is organized**.
  
  - **Key Points**:
    - **Vertex Array Object (VAO)**:
       Remembers how vertex data (points, colors, etc.) is structured.
    - **Vertex Buffer Object (VBO)**:
       Actually holds the vertex data inside GPU memory.
  
  #### 📍 Code Example 
  
  ```c++
  // Function to create and set up a simple triangle in OpenGL
  void CreateTriangle()
  {
      // 1. Define vertices (points) for a triangle (x, y, z)
      GLfloat vertices[] = {
          -1.0f, -1.0f, 0.0f,   // bottom-left corner
           1.0f, -1.0f, 0.0f,   // bottom-right corner
           0.0f,  1.0f, 0.0f    // top-center vertex
      };
  
      // 2. Generate a Vertex Array Object (VAO)
      glGenVertexArrays(1, &VAO);
  
      // 3. Bind the VAO (activate it to store configurations)
      glBindVertexArray(VAO);
  
      // 4. Generate a Vertex Buffer Object (VBO)
      glGenBuffers(1, &VBO);
  
  	// 5. Bind the VBO (activate it to store configurations)
  	glBindBuffer(GL_ARRAY_BUFFER, VBO); // store vertex data using GL_ARRAY_BUFFER
  
      // 6. Upload vertex data (triangle points) to GPU memory
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      
  
      // 5. Tell OpenGL how to interpret the vertex data:
      glVertexAttribPointer(
          0,          // attribute location (matches shader location=0)
          3,          // 3 values per vertex (X, Y, Z)
          GL_FLOAT,   // data type
          GL_FALSE,   // data not normalized (leave as-is)
          0,          // stride (0 means tightly packed data)
          0           // offset (start reading from beginning)
      );
  
      // 6. Enable the vertex attribute (location 0 in shader)
      glEnableVertexAttribArray(0);
  
      // 7. Unbind VBO to avoid accidental modification
      glBindBuffer(GL_ARRAY_BUFFER, 0);
  
      // 7. Unbind VAO for safety
      glBindVertexArray(0);
  }
  ```
  
  #### 📍 Thought Process & Analysis
  
  - `glGenVertexArrays(1, &VAO);`This **generates**  a new **VAO** ID into variable 'VAO'. After generation,use `glBindVertexArray(VAO);` to use this VAO. **VBO** similarly. After "Bind", OpenGL will remember which pair of VAO/VBO now is.
  - VBO buffer is just memory space on GPU, typically need **one buffer per type of vertex data**
    - `glBindBuffer()` -https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
    - `glBufferData()` -https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml
  
  - `glVertexAttribPointer()` & `glEnableVertexAttribArray()` - **Connect your VBO (vertex data) to your vertex shader inputs.**
    - [`glVertexAttribPointer()`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml) -Telling OpenGL how to read vertex data from your VBO and pass it to your vertex shader. 
    - [`glEnableVertexAttribArray()`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml)-Must enable the **same location number** that you used in your shader. By default, OpenGL **ignores all attributes**. You must turn them **ON** with . 


  ## 🚩 **Vertex Shader and Fragment Shader** 

  - ### 🔸 Simple Vertex Shader
    
    #### 📍 Core Concepts
    
    - **Definition**:
       The vertex shader runs once for every vertex. It processes positions and passes them down the pipeline.
    - **Key Points**:
      - **layout(location = 0) in vec3 pos;**
         Gets data from `glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ...);`
      - **gl_Position**
         Mandatory output. Defines where this vertex will show up on the screen (clip space).
    
    #### 📍 Code Example
    
    ```glsl
    #version 330
    
    layout (location = 0) in vec3 pos;
    
    void main()
    {
        gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
    }
    ```
    
    #### 📍 Thought Process & Analysis
    
    - **gl_Position = vec4(...)**
       Converts `pos` (vec3) into `vec4` because OpenGL needs 4D (homogeneous) coordinates.
    - `layout(location = 0)` must match your `glVertexAttribPointer(0, ...)` setting.
    - **vec3** = GLSL built-in type for Each vertex is **3 floats** = position (x, y, z)

  - ### 🔸 Simple Fragment Shader

    #### 📍 Core Concepts

    - **Definition**:
       The fragment shader runs once for every pixel ("fragment") inside the shape, setting its color.
    - **Key Points**:
      - **out vec4 colour;**
         This defines the final color of the pixel.
      - **vec4(1.0, 0.0, 0.0, 1.0)**
         This sets **red** color (RGB = 1, 0, 0) with full opacity.

    #### 📍 Code Example

    ```glsl
    #version 330
    
    out vec4 colour;
    
    void main()
    {
        colour = vec4(1.0, 0.0, 0.0, 1.0);
    }
    ```

    #### 📍 Thought Process & Analysis

    - **out vec4 colour**
       The final color output of the pixel that will show on screen.
    - **vec4(1, 0, 0, 1)**
       Means full **red** (R=1, G=0, B=0) with full **alpha** (A=1 = no transparency).
    - **Every pixel inside the triangle will be fully red**.

    ------

    🟢 These two shaders together:

    - **Vertex Shader** ➡️ positions the triangle.
    - **Fragment Shader** ➡️ colors it red.

  ## 🚩 Shader program 

### 🔸 Adding Shader function

#### 📍 Core Concepts

- A shader object is used to maintain the source code strings that define a shader.
- In a shader object, compilation status will be stored.
- Needs to Attaches a shader object to a program object.

📍 Code Example

```c++
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
```

📍 Thought Process & Analysis

* [`glCreateShader()`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml) -Creates an empty shader object and returns a non-zero value by which it can be referenced.
* [`glShaderSource`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glShaderSource.xhtml) — Replaces the source code in a shader object
* [`glCompileShader`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCompileShader.xhtml) compiles the source code strings that have been stored in the shader object specified by *`shader`*.
* [`glAttachShader`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml) attaches the shader object specified by *`shader`* to the program object specified by *`program`*.

----

### 🔸 Creating a shader program

#### 📍 Core Concepts

- This function **creates**, **links**, and **validates** a complete shader program.
-  A program object is an object to which shader objects can be attached.
- Attached shader objects will be used to create an executable that will run on the programmable processor.
- `glLinkProgram` takes all the **attached shaders** (like vertex and fragment) and **links** them into a single **executable GPU program**.

#### 📍 Code Example

```c++
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
```

------

#### 📍 Thought Process & Analysis

- `glCreateProgram` creates an empty program object and returns a non-zero value by which it can be referenced.
- `glAttachShader` attaches the shader object specified by *`shader`* to the program object specified by *`program`*.
- `glLinkProgram` links the program object specified by *`program`*. 

----

**🔸Using the shader program & Initiating Draw**

📍 Core Concepts

* for Using shader program:
  * When you create a shader, an ID is given (like with VAOs and VBOs). 
  * Simply call `glUseProgram(shaderID)` 
  * All draw calls from then on will use that shader,  shader is stopped by using `glUseProgram(0)`

* for Initiating Draw:
  1. Activate Shader Program you want to use. 
  2. Bind VAO of object you want to draw. 
  3. Call `glDrawArrays`, which initiates the rest of the pipeline.

```C++
int main()
{
	// Initalize GLFW
    ...
	// Get OpenGL ready
	...
	// Initialize GLEW
	...	
	//set up viewport size for OpenGL to draw in
	...

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

		glUseProgram(shader);
		//printf("Shader Program ID: %d\n", shader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
        //unbind 
		glBindVertexArray(0);
		glUseProgram(0);

		//swap the front and back buffers, show the rendered result
		glfwSwapBuffers(mainWindow);
	}

	return 0;
}
```

📍 Thought Process & Analysis

* `CreateTriangle()` -Create triangle points and store information into **VAO**
* `CompileShaders()` -Create shader program for later using
* `glUseProgram` — Installs a program object as part of current rendering state
* `glDrawArrays` — When `glDrawArrays` is called, it uses *`count`* sequential elements from each enabled array to construct a sequence of geometric primitives, VAO points to these array

### 🎯 Breakdown:

1. **Before drawing**:

   - You upload vertex data to the GPU using VBO.

   - You link that data to a shader attribute using:

     ```c++
     glVertexAttribPointer(...);
     glEnableVertexAttribArray(...);
     ```

2. **When you call** `glDrawArrays(...)`:

   - OpenGL:

     - Uses the VAO to find the right VBO and layout.

     - Starts feeding vertex data into the **vertex shader**.

     - Each vertex goes into the shader input like:

       ```glsl
       layout(location = 0) in vec3 pos;
       ```

------

### 📌 Example Flow:

```
cppCopyEditglBindVertexArray(VAO);       // VAO knows which VBO + layout
glUseProgram(shader);         // Shader is active
glDrawArrays(GL_TRIANGLES, 0, 3); // 🔥 Now vertex data goes into shader
```

→ At this moment, the GPU takes 3 vertices
 → Passes each one to your vertex shader
 → The output of vertex shader goes to the rest of the pipeline

## ✅ Why `glBindVertexArray(VAO)` still works after unbinding?

Because **VAO stores all settings** when it's bound.

Even if you unbind later, OpenGL already **saved**:

- Which VBO was bound
- How the vertex data is formatted (`glVertexAttribPointer`)
- Which attributes are enabled (`glEnableVertexAttribArray`)



![image-20250329204520174](C:\Users\t\AppData\Roaming\Typora\typora-user-images\image-20250329204520174.png)