#pragma once
#include <glad/glad.h>
#include <string>


class RenderSkybox
{
private:
	std::string mesh = "src/Meshes/Cube.obj";
	std::string shader ="skybox";
	GLuint textureID;
	std::string posXFile, posYFile, posZFile, negXFile, negYFile, negZFile;
public:
	RenderSkybox(const std::string& posXFile_, const std::string& posYFile_, const std::string& posZFile_,
	             const std::string& negXFile_, const std::string& negYFile_, const std::string&);

	bool OnCreate();
	std::string GetFilename() const { return posXFile; }
	GLuint GetTextureID() const { return textureID; }
};
