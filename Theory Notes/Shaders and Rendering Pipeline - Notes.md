### **Shaders and Rendering Pipeline - Notes**

------

## **1. Overview**

The **Rendering Pipeline** is a structured sequence of stages that the **GPU** follows to process and render an image to the screen.

Four of these stages are **programmable** via **Shaders**:

- **Vertex Shader**
- **Tessellation Shader**
- **Geometry Shader**
- **Fragment Shader**

Shaders are written in **GLSL (OpenGL Shading Language)** or HLSL (High-Level Shading Language) (for DirectX).

------

## **2. Stages of the Rendering Pipeline**

| **Stage**                     | **Notes**                                                    | Where                           |
| ----------------------------- | ------------------------------------------------------------ | :------------------------------ |
| **1. Vertex Specification**   | Creating **VAO/VBO**，Initiating Draw                        | Done in the application itself. |
| **2. Vertex Shader**          | Processes **individual vertices**,  store things in **gl_Position**. | Programmable                    |
| **3. Tessellation Shader**    | this shader dynamically **subdivides primitives** to improve detail and optimize level of detail | Programmable                    |
| **4. Geometry Shader**        | Operates on **entire primitives** ,allowing **modifications** and **new geometry creation**. | Programmable                    |
| **5. Vertex Post-Processing** | Includes **Transform Feedback** (for reusing vertex data) and **Clipping** (removes out-of-view primitives). Converts coordinates from **clip-space** to **window-space**. |                                 |
| **6. Primitive Assembly**     | Groups **vertices** into **primitives** (triangles, lines, etc.) and performs **Face Culling** to remove **back-facing** primitives. |                                 |
| **7. Rasterization**          | Converts **primitives into fragments**, interpolating values (e.g., color, depth) across pixels. |                                 |
| **8. Fragment Shader**        | Determines **pixel colors** by handling **lighting, textures, and shading**. Often the most complex shader in real-time rendering. | Programmable                    |
| **9. Per-Sample Operations**  | Series of tests run to see if the fragment should be drawn Includes **Depth Testing** , **Color Blending** , and **Frame Buffer Operations**. |                                 |

------

## **3. Shader Programs**

- A **Shader Program** is a combination of **compiled shaders** (at least a **Vertex Shader**).
- Created using OpenGL functions:
  1. **Create Program**
  2. **Create Shaders (Vertex, Fragment, etc.)**
  3. **Attach Shader Source Code**
  4. **Compile Shaders**
  5. **Attach shaders to program**
  6. **Link Program**
  7. **Validate Program** *(optional but Highly recommended!)*

------

## **4. Key Terms and Definitions**

| Term                           | Definition                                                   |
| ------------------------------ | ------------------------------------------------------------ |
| **Rendering Pipeline**         | A sequence of GPU processing stages that transform **vertex data** into a **rendered image**. |
| **Shader**                     | A small **GPU program** written in **GLSL** or **HLSL** that controls rendering stages. |
| **Vertex Shader**              | A **mandatory** shader that processes individual **vertices** and determines their **final position**. |
| **Tessellation Shader**        | A shader that **subdivides** primitives into **smaller** parts for **higher detail**. |
| **Geometry Shader**            | A shader that processes **entire primitives** and can modify or generate new geometry. |
| **Fragment Shader**            | A shader that **determines pixel colors** by applying **lighting and textures**. |
| **Vertex Specification**       | Defines and organizes **vertex data** for rendering.         |
| **Vertex**                     | A **point in 3D space**, typically defined by **x, y, z** coordinates. |
| **Primitive**                  | A shape composed of **multiple vertices**, commonly **triangles, lines, or points**. |
| **Primitive Assembly**         | Groups **vertices into primitives** and performs **Face Culling**. |
| **Face Culling**               | Removes **back-facing** or **hidden** primitives for better performance. |
| **Rasterization**              | Converts **primitives into fragments** (potential pixels).   |
| **Fragment**                   | A **potential pixel**, containing **color, depth, and texture** data. |
| **Depth Testing**              | Determines which **fragments** are **visible** based on their depth. |
| **Color Blending**             | Blends **overlapping** fragment colors (e.g., transparency effects). |
| **Vertex Array Object (VAO)**  | Defines the **structure** of a **vertex** (position, color, texture, etc.). |
| **Vertex Buffer Object (VBO)** | Stores actual **vertex data** in **GPU memory**.             |
| **Frame Buffer**               | A memory area where **rendered images** are stored before display. |
| **Shader Program**             | A **compiled and linked** set of **shaders** executed during rendering. |

## 