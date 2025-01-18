#include "triangle3D.h"

Triangle3D::Triangle3D(const glm::vec3& position) : RenderableObject(
    // Punkty
     {
         0.0f,  0.5f, 0.0f,  // lewy górny
        -0.3f, 0.0f, 0.0f,  // lewy dolny
         0.0f, -0.5f, 0.0f,  // prawy dolny
         0.3f,  0.0f, 0.0f   // prawy górny
    },
    // Kolory
    {
        1.0f, 1.0f, 1.0f,  // lewy górny
        1.0f, 1.0f, 1.0f,  // lewy dolny
        1.0f, 1.0f, 1.0f,  // prawy dolny
        1.0f, 1.0f, 1.0f   // prawy górny
    },
    // Tekstura
    {
        0.0f, 1.0f,  // lewy górny
        0.0f, 0.0f,  // lewy dolny
        1.0f, 0.0f,  // prawy dolny
        1.0f, 1.0f   // prawy górny
    },
    GL_QUADS,
    position
) {}

