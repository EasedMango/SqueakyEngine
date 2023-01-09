#pragma once
#include <glad/glad.h>
#include <string>

	class RenderTexture
	{

	private:
		std::string fileName;
		GLuint textureID;
	public:
		RenderTexture(const std::string& filename);

		~RenderTexture();

		bool OnCreate();

		GLuint GetTextureID() const;
		std::string GetFileName()const;
	};

