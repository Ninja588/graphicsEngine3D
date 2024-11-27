#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include "RenderableObject.h"

class Triangle3D : public RenderableObject {
public:
    Triangle3D(const glm::vec3& position);
};

#endif // TRIANGLE3D_H