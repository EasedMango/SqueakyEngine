#pragma once
#include "RenderTexture.h"
#include "RenderShader.h"
class RenderMaterial
{
private:
	RenderShader* shader;
	RenderTexture* texture;
	const unsigned int id;

public:
	RenderMaterial(const RenderShader& shaderName, const RenderTexture& textureName, unsigned int id);

};

