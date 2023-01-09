#include "RenderTexture.h"

#include <stb_image.h>

RenderTexture::RenderTexture(const std::string& filename) : fileName(filename),textureID(0)
{
	
}

RenderTexture::~RenderTexture()
{
	glDeleteTextures(1, &textureID);
}

bool RenderTexture::OnCreate()
{
    int width, height, channels;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);


    unsigned char* img = stbi_load(fileName.c_str(), &width, &height, &channels, 0);
    if (img == nullptr)
    {
        printf("Error in loading the image\n");
        return false;

    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);


    if (channels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    else if (channels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(img);

    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

GLuint RenderTexture::GetTextureID() const
{ return textureID; }

std::string RenderTexture::GetFileName() const
{ return fileName; }
