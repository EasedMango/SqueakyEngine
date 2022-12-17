#include "Shader.h"

Shader::Shader(const std::string& filenameV, const std::string& filenameF): Component(nullptr),
                                                                            filenameV(filenameV),
                                                                            filenameF(filenameF)
{
}

bool Shader::OnCreate()
{
	return true;
}

void Shader::OnDestroy()
{
}

void Shader::Update(const float deltaTime)
{
}

void Shader::Render() const
{
}

void Shader::RenderGui()
{
}

Shader::~Shader()
= default;
