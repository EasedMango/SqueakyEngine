#pragma once
#include <glad/glad.h>
#include "Component.h"
class Material : public Component
{
	
	
	const char* fileName;
	GLuint textureID;
public:
	Material( const char* fileName_="");
	//Material();
	~Material();


	 bool OnCreate() override;
	 void OnDestroy()override;
	 void Update(const float deltaTime)override;
	 void Render() const override;
	 void RenderGui() override;
	 inline GLuint getTextureID() const { return textureID; }

};

