#pragma once
#include <glad/glad.h>
#include "Component.h"
#include <unordered_map>
class Shader : public Component
{
	Shader(const Shader&) = delete;
	Shader(Shader&&) = delete;
	Shader& operator = (const Shader&) = delete;
	Shader& operator = (Shader&&) = delete;
private:
	const char* vsFilename;
	const char* fsFilename;
	GLuint shaderID;
	GLuint vertShaderID;
	GLuint fragShaderID;
	std::unordered_map<std::string, GLuint> uniformMap;

	std::string ReadTextFile(const char* file_path);
	bool CompileShader(GLuint& id, const char* fileName, GLint &status);
	bool CompileAttach();
	bool Link();
	void SetUniformLocations();
	std::string ReadFile(const char* filename);
public:
	Shader( const char* vsFilename_= "src/Shaders/defaultVert.glsl", const char* fsFilename_= "src/Shaders/defaultFrag.glsl");
	~Shader();


	inline GLuint GetProgram() const { return shaderID; }
	GLuint GetUniformID(std::string name);


	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) ;
	void Render() const ;
	void RenderGui() override;
};

