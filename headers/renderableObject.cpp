#include "RenderableObject.h"
#include <iostream>

RenderableObject::RenderableObject(const std::vector<float>& verts, const std::vector<float>& cols, const std::vector<float>& tex, GLenum primitiveType, const glm::vec3& pos)
    : vertices(verts), colors(cols), texCoords(tex), primitiveType(primitiveType), position(pos) {}

void RenderableObject::draw(const glm::mat4& view, const glm::mat4& projection, GLuint textureID, Shader shader) {
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    shader.use();

    glm::vec3 lightPos = glm::vec3(0.0f, 3.0f, 0.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 0.8f);
    float lightRadius = 5.0f;

    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
    glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glUniform3fv(glGetUniformLocation(shader.ID, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shader.ID, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform1f(glGetUniformLocation(shader.ID, "lightRadius"), lightRadius);

    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    GLuint viewLoc = glGetUniformLocation(shader.ID, "view");
    GLuint projectionLoc = glGetUniformLocation(shader.ID, "projection");

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, objectScale);

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    if (textureID > 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glUniform1i(glGetUniformLocation(shader.ID, "textureSampler"), 0);
    }

    GLuint vao, vboVertices, vboColors, vboTexCoords;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vboTexCoords);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glDrawArrays(primitiveType, 0, vertices.size() / 3);

    glBindVertexArray(0);
    glDeleteBuffers(1, &vboVertices);
    glDeleteBuffers(1, &vboTexCoords);
    glDeleteVertexArrays(1, &vao);

    glUseProgram(0);
}

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
    model = glm::scale(model, objectScale);

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

void RenderableObject::translate(glm::vec3 newPos) {
    position = newPos;
}

void RenderableObject::scale(glm::vec3 newScale) {
    objectScale = newScale;
}
