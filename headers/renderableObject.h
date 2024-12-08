#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class RenderableObject {
public:
    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<float> texCoords;
    glm::vec3 position;
    GLenum primitiveType;
    float rotationAngle;
    glm::vec3 objectScale = glm::vec3(1.0f);

    RenderableObject(const std::vector<float>& verts, const std::vector<float>& cols, const std::vector<float>& tex, GLenum primitiveType, const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f));
    virtual void draw(const glm::mat4& view, const glm::mat4& projection, GLuint textureID);

    void setColor(const std::vector<float>& newColors);
    void updateRotation(float deltaTime);
    void translate(glm::vec3 newPos);
    void scale(glm::vec3 newScale);
};

#endif // RENDERABLE_OBJECT_H
