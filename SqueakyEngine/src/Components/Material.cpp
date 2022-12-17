#include "Material.h"


 Material::Material(const std::string& filename) : Component(nullptr),
filename(filename)
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

 Material::~Material()
= default;

 std::string Material::GetFilename() const
{
	return filename;
}
