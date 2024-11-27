#ifndef CUBE_H
#define CUBE_H

#include "RenderableObject.h"

class Cube : public RenderableObject {
public:
    Cube(const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f));

    void draw(const glm::mat4& view, const glm::mat4& projection, GLuint textureID) override;

private:
    std::vector<unsigned int> indices;
    std::vector<float> normals;
};

#endif // CUBE_H
