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

  ## 🚩 Section 3 Title

  ### 🔸 Subtopic 3.1

  #### 📍 Practical Steps

  1. Step 1: Concise description
  2. Step 2: Concise description

  #### 📍 Tips and Cautions

  - **Tip 1**: Detailed explanation
  - **Tip 2**: Detailed explanation

  ## 📝 Next Steps (Optional, good for ongoing updates)

  - 

  ## 📚 References

  - Official Documentation
  - Relevant Blog Article