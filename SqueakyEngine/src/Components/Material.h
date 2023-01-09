#pragma once
#include "Component.h"
#include <string>

class Material :
	public Component
{
public:

private:
	std::string textureFilename;
	std::string shaderFilename;
	unsigned int id;



public:
	Material(std::string filenameTexture, std::string filenameShader);

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void RenderGui() override;

	std::basic_string<char> GetTextureFilename() const;
	std::basic_string<char> GetShaderFilename() const;
	~Material() override;
};

