#pragma once
#include <glad/glad.h>
#include <string>

	class RenderMaterial
	{

	private:
		std::string fileName;
		GLuint textureID;
	public:
		RenderMaterial(const std::string& filename);

		~RenderMaterial();

		bool OnCreate();

		GLuint GetTextureID() const;
		std::string GetFileName()const;
	};

