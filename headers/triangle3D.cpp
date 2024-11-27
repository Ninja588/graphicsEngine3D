#include "triangle3D.h"

Triangle3D::Triangle3D(const glm::vec3& position) : RenderableObject(
    // Punkty
    {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f, 
        0.0f, 0.5f, 0.0f, 
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f, 
        0.0f, 0.5f, 0.0f,  
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.0f, 0.5f, 0.0f,   
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f  
    },
    // Kolory
    {
        1.0f, 1.0, 1.0, 
        1.0, 1.0f, 1.0, 
        1.0, 1.0, 1.0f, 
        1.0f, 1.0, 1.0, 
        1.0, 1.0, 1.0f, 
        1.0, 1.0f, 1.0, 
        1.0f, 1.0, 1.0, 
        1.0, 1.0f, 1.0, 
        1.0, 1.0, 1.0f, 
        1.0f, 1.0, 1.0, 
        1.0, 1.0, 1.0f, 
        1.0, 1.0f, 1.0
    },
    // Tekstura
    {
        0.5f, 1.0f, // gora
        0.0f, 0.0f, // lewy dol
        1.0f, 0.0f,  // prway dol

        0.5f, 1.0f,
        0.0f, 0.0f, 
        1.0f, 0.0f,  

        0.5f, 1.0f,  
        0.0f, 0.0f,
        1.0f, 0.0f, 
        
        0.5f, 1.0f,  
        0.0f, 0.0f,
        1.0f, 0.0f  
    },
    GL_TRIANGLES,
    position
) {}

