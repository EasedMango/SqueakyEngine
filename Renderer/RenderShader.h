#pragma once
#include <glad/glad.h>
#include <unordered_map>
#include <string>
class RenderShader
{
	//RenderShader(const RenderShader&) = delete;
	//RenderShader(RenderShader&&) = delete;
	//RenderShader& operator =(const RenderShader&) = delete;
	//RenderShader& operator =(RenderShader&&) = delete;
private:
	std::string shaderFilePath = "src/Shaders/";
	std::string filename;

	GLuint shaderID;
	GLuint vertShaderID;
	GLuint fragShaderID;
	std::unordered_map<std::string, GLuint> uniformMap;

	std::string ReadTextFile(const char* file_path) const;
	bool CompileShader(GLuint& id, std::string fileName, GLint& status);
	bool CompileAttach();
	bool Link() const;
	void SetUniformLocations();
	static std::string ReadFile(const char* filename);
public:
	RenderShader(const std::string& filename_ = "default");
	~RenderShader();

	std::string GetFileName()const;

	GLuint GetProgram() const;
	GLuint GetUniformID(const std::string& name);

	bool OnCreate();


};
