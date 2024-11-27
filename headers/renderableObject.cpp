#include "RenderableObject.h"
#include <iostream>

RenderableObject::RenderableObject(const std::vector<float>& verts, const std::vector<float>& cols, const std::vector<float>& tex, GLenum primitiveType, const glm::vec3& pos)
    : vertices(verts), colors(cols), texCoords(tex), primitiveType(primitiveType), position(pos) {}

void RenderableObject::draw(const glm::mat4& view, const glm::mat4& projection, GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glColorPointer(3, GL_FLOAT, 0, &colors[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);

    if(textureID > 0) glBindTexture(GL_TEXTURE_2D, textureID);

    glm::mat4 model = glm::mat4(1.0f); 
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view * model));

    glDrawArrays(primitiveType, 0, vertices.size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glDisable(GL_TEXTURE_2D);
}

void RenderableObject::setColor(const std::vector<float>& newColors) {
    if (newColors.size() == colors.size()) {
        colors = newColors;
    } else {
        std::cerr << "Error: Nowy kolor nie zgadza sie z kolorem poprzednim (wielkosc wektora)" << std::endl;
    }
}

void RenderableObject::updateRotation(float deltaTime) {
    rotationAngle += 50.0f * deltaTime;
    if(rotationAngle > 360.0f) rotationAngle -= 360.0f;
}
