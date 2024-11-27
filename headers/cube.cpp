#include "Cube.h"

std::vector<float> cubeVertices = {
    // przod
    -1.0f, -1.0f, -1.0f, // 0
     1.0f, -1.0f, -1.0f, // 1
     1.0f,  1.0f, -1.0f, // 2
    -1.0f,  1.0f, -1.0f, // 3
    // tyl
    -1.0f, -1.0f,  1.0f, // 4
     1.0f, -1.0f,  1.0f, // 5
     1.0f,  1.0f,  1.0f, // 6
    -1.0f,  1.0f,  1.0f  // 7
};

std::vector<unsigned int> cubeIndices = {
    // gora
    0, 1, 2,
    2, 3, 0,
    // tyl 
    4, 5, 6,
    6, 7, 4,
    // lewo 
    4, 0, 3,
    3, 7, 4,
    // prawo 
    1, 5, 6,
    6, 2, 1,
    // gora 
    3, 2, 6,
    6, 7, 3,
    // dol 
    4, 5, 1,
    1, 0, 4
};

std::vector<float> cubeNormals = {
    // Normals przod
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    // Normals tyl
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    // Normals lewo
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    // Normals prawo
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    // Normals gora
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    // Normals dol
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f
};

std::vector<float> cubeColors = {
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f
    // 0.0f, 1.0f, 0.0f,
    // 0.0f, 0.0f, 1.0f,  
    // 1.0f, 1.0f, 0.0f,
    // 1.0f, 0.0f, 1.0f,
    // 0.0f, 1.0f, 1.0f,
    // 1.0f, 0.5f, 0.0f,
    // 0.5f, 0.0f, 0.5f
};

std::vector<float> cubeTextures = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,

    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f
};

Cube::Cube(const glm::vec3& pos)
    : RenderableObject(cubeVertices, cubeColors, cubeTextures, GL_TRIANGLES, pos), indices(cubeIndices), normals(cubeNormals) {}

void Cube::draw(const glm::mat4& view, const glm::mat4& projection, GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glColorPointer(3, GL_FLOAT, 0, &colors[0]);
    glNormalPointer(GL_FLOAT, 0, &normals[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view * model));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
}
