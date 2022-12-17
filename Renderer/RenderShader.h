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
	std::string vsFilename;
	std::string fsFilename;
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
	RenderShader(std::string vsFilename_ = "defaultVert.glsl", std::string fsFilename_ = "defaultFrag.glsl");
	~RenderShader();

	std::string GetVertFileName()const;
	std::string GetFragFileName()const;
	GLuint GetProgram() const;
	GLuint GetUniformID(std::string name);

	bool OnCreate();


};
