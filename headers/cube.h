#ifndef CUBE_H
#define CUBE_H

#include "RenderableObject.h"

class Cube : public RenderableObject {
public:
    Cube(const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f));

    void draw(const glm::mat4& view, const glm::mat4& projection, GLuint textureID) override;

    void scale(glm::vec3 newScale);

private:
    std::vector<unsigned int> indices;
    std::vector<float> normals;
    glm::vec3 objectScale = glm::vec3(1.0f);
};

#endif // CUBE_H
