#include "Material.h"


Material::Material(std::string filenameTexture, std::string filenameShader) : Component(nullptr), textureFilename(
	                                                                              std::move(filenameTexture)),
                                                                              shaderFilename(
	                                                                              std::move(filenameShader)), id(0)
{
}

 bool Material::OnCreate()
{
	return true;
}

 void Material::OnDestroy()
{
}

 void Material::Update(const float deltaTime)
{
}

 void Material::Render() const
{
}

 void Material::RenderGui()
{
}

std::string Material::GetTextureFilename() const
{ return textureFilename; }

 Material::~Material()
= default;

 std::string Material::GetShaderFilename() const
{
	return shaderFilename;
}


