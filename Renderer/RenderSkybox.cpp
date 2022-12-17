#include "RenderSkybox.h"

#include <stb_image.h>

RenderSkybox::RenderSkybox(const std::string& posXFile_, const std::string& posYFile_, const std::string& posZFile_,
                           const std::string& negXFile_,
                           const std::string& negYFile_, const std::string& negZFile_) : posXFile((posXFile_)),
	posYFile((posYFile_)), posZFile((posZFile_)), negXFile((negXFile_)), negYFile((negYFile_)), negZFile((negZFile_))
{
}

bool RenderSkybox::OnCreate()
{
	unsigned char* img;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, channels;


	std::string posnegArray[6]{posXFile, negXFile, posYFile, negYFile, posZFile, negZFile};

	for (int i = 0; i < 6; ++i)
	{
		img = stbi_load(posnegArray[i].c_str(), &width, &height, &channels, 0);
		if (img == nullptr)
		{
			printf("Error in loading the image\n");
			return false;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		stbi_image_free(img);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}
