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
	unsigned int shaderID;
	GLuint vertShaderID;
	GLuint fragShaderID;
	std::unordered_map<std::string, GLuint> uniformMap;

	char* ReadTextFile(const char* fileName);
	bool CompileShader(GLuint& id, const char* fileName, GLint status);
	bool CompileAttach();
	bool Link();
	void SetUniformLocations();

public:
	Shader(Component* parent_, const char* vsFilename_, const char* fsFilename_);
	~Shader();


	inline GLuint GetProgram() const { return shaderID; }
	GLuint GetUniformID(std::string name);


	bool OnCreate() ;
	void OnDestroy() ;
	void Update(const float deltaTime) ;
	void Render() const ;

};

