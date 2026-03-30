#pragma once
#include <glad/gl.h>
#include "stb_image.h"
#include <stdexcept>
#include <string>

class Texture {
public:
    GLuint id;
    int width;
    int height;
    int channels;

    Texture(const std::string &path) {
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data =
            stbi_load(path.c_str(), &width, &height, &channels, 4);

        if (!data) {
            throw std::runtime_error("Failed to load texture: " + path);
        }

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    ~Texture() { glDeleteTextures(1, &id); }

    void bind(unsigned int unit = 0) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, id);
    }
};
