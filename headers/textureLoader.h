#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <GL/glew.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class TextureLoader {
public:
    static GLuint loadTexture(const char* path) {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "Nie udalo sie wczytac tekstury" << std::endl;
        }
        stbi_image_free(data);

        return textureID;
    }
};

#endif // TEXTURE_LOADER_H
