#include "Material.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Material::Material(Component* parent_, const char* fileName_) : fileName(fileName_), textureID(0) ,Component(parent_) {

}
Material::~Material() {
	glDeleteTextures(1, &textureID);
}

bool Material::OnCreate() {
	int width, height, channels;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);


	unsigned char* img = stbi_load(fileName, &width, &height, &channels, 0);
	if (img == NULL) {
		printf("Error in loading the image\n");
		return 0;
		exit(1);

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
	return 1;

}
void Material::OnDestroy() {}

void Material::Render() const {}

void Material::RenderGui()
{
}

void Material::Update(const float deltaTime) {

}