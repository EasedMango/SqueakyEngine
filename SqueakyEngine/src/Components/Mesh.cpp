#include "Mesh.h"



Mesh::Mesh(const std::string& filename_) : Component(nullptr), filename(filename_)
{
}

Mesh::~Mesh()
= default;

bool Mesh::OnCreate()
{
	return true;
}

void Mesh::OnDestroy()
{
}

void Mesh::Update(const float deltaTime)
{
}

void Mesh::Render() const
{
}

void Mesh::RenderGui()
{
}
