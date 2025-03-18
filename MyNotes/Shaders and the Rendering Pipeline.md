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

  - ✅ Section 1: Vertex Specification
  - ✅ Section 2: Description
  - ⬜️ Section 3: Description

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
    - `glVertexAttribPointer()` -Telling OpenGL how to read vertex data from your VBO and pass it to your vertex shader. -https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
    - `glEnableVertexAttribArray()` -Must enable the **same location number** that you used in your shader. By default, OpenGL **ignores all attributes**. You must turn them **ON** with . -https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml


  ## 🚩 Section 2 Title

  ### 🔸 Subtopic 2.1

  #### 📍 Core Content

  - Clearly describe specific knowledge points.

  #### 📍 Examples or Images

  > Format for images:

  ```
  ![Image Description](image-link)
  ```

  #### 📍 Common Issues & Solutions

  - **Issue 1**: Detailed description
    - **Solution**: Step-by-step explanation
  - **Issue 2**: Detailed description
    - **Solution**: Step-by-step explanation

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