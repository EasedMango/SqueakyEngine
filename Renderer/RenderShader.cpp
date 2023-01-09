#include "RenderShader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <utility>

RenderShader::RenderShader(const std::string& filename_) :
shaderID(0), vertShaderID(0), fragShaderID(0)
{
    this->filename = (filename_);


}

std::string RenderShader::ReadFile(const char* filename) 
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string shaderCode;

    std::ifstream ShaderFile;

    // ensure ifstream objects can throw exceptions:
    ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        ShaderFile.open(filename);

        std::stringstream ShaderStream;
        // read file's buffer contents into streams
        ShaderStream << ShaderFile.rdbuf();

        // close file handlers
        ShaderFile.close();

        // convert stream into string
        shaderCode = ShaderStream.str();
    }
    catch (std::ifstream::failure &e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return shaderCode;
}

RenderShader::~RenderShader()
= default;

std::string RenderShader::GetFileName() const
{
    return filename;
}




GLuint RenderShader::GetProgram() const
{ return shaderID; }

std::string RenderShader::ReadTextFile(const char* file_path) const
{
    // Read the Vertex RenderShader code from the file
    std::string shaderCode;
    std::ifstream shaderStream(file_path, std::ios::in);
    if (shaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
        return shaderCode;
    }
    std::cout << std::filesystem::current_path() << std::endl;
   // Logger::Info("Couldn't open file ");
    getchar();
    return nullptr;
}

 bool RenderShader::CompileShader(GLuint& id, std::string fileName, GLint& status)
{
    glCompileShader(id);
    printf("Compiled\n");
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    std::cout << "status: " << status << std::endl;
    if (status == 0)
    {
        GLsizei errorLogSize = 0;
        std::string errorLog = fileName;
        errorLog += ":\n";
        GLsizei titleLength = errorLog.length();
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errorLogSize);
        errorLog.resize(titleLength + errorLogSize);
        glGetShaderInfoLog(id, errorLogSize, &errorLogSize, &errorLog[titleLength]);
        std::cout << (errorLog);
        std::string thr("");
        throw thr;
    }

    return true;
}

bool RenderShader::CompileAttach()
{
    GLint status = 0;
    try
    {
        
        printf("start vert\n");
        std::string vertFs = (shaderFilePath + filename+ std::string(".vert"));
        const char* vertFile = vertFs.c_str();
        std::cout << (vertFile) << std::endl;
        std::string vertS = ReadTextFile(vertFile);
        const char* vert = vertS.c_str();
        vertShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShaderID, 1, &vert, nullptr);
        CompileShader(vertShaderID, filename, status);

        printf("start frag\n");
        std::string fragFs = (shaderFilePath + filename + std::string(".frag"));
        const char* fragFile = fragFs.c_str();
        std::cout << (fragFile) << std::endl;
        std::string fragS = ReadTextFile(fragFile);
        const char* frag = fragS.c_str();
        fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShaderID, 1, &frag, nullptr);
        CompileShader(fragShaderID, filename, status);



        printf("Create RenderShader\n");
        shaderID = glCreateProgram();
        printf("attach vert\n");
        glAttachShader(shaderID, vertShaderID);
        printf("attach frag\n");
        glAttachShader(shaderID, fragShaderID);
        //if (vert) delete[] vert;
        //if (frag) delete[] frag;
    }
    catch (std::string error)
    {
        printf("%s\n", &error[0]);
        std::cout << (error);
        return false;
    }

    return true;
}

bool RenderShader::Link() const
{
    int InfoLogLength;
    GLint status;
    try
    {
        glLinkProgram(shaderID);
        printf("Linked\n");
        /// Check for errors
        glGetProgramiv(shaderID, GL_LINK_STATUS, &status);
        GLsizei errorLogSize = 0;
        std::string errorLog;
        glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
        errorLog.resize(errorLogSize);
        glGetProgramInfoLog(shaderID, errorLogSize, &errorLogSize, &errorLog[0]);
        std::cout << (errorLog);
        if (status == 0)
        {
            throw errorLog;
        }
    }
    catch (std::string error)
    {
        std::cout << (error);
        return false;
    }
    glDetachShader(shaderID, vertShaderID);
    glDetachShader(shaderID, fragShaderID);

    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);
    return true;
}

void RenderShader::SetUniformLocations()
{
    GLint i;
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 24; // maximum name length
    //glGetProgramiv(shaderID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformListLength);
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    glGetProgramiv(shaderID, GL_ACTIVE_ATTRIBUTES, &count);
    printf("There are %d active Attributes\n", count);

    //printf("Active Attributes: %d\n", count);
    std::string activeAttributeList = "Attributes:";
    for (i = 0; i < count; i++)
    {
        glGetActiveAttrib(shaderID, static_cast<GLuint>(i), bufSize, &length, &size, &type, name);
        activeAttributeList += std::string("\n") + name;
        //uniformMap.insert(std::make_pair( name, (GLuint)i));
        //printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
    }


    std::cout << (activeAttributeList);


    glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &count);
    printf("There are %d active Uniforms\n", count);
    std::string activeUniformList = "Uniforms:";
    for (i = 0; i < count; i++)
    {
        glGetActiveUniform(shaderID, static_cast<GLuint>(i), bufSize, &length, &size, &type, name);
        uniformMap.insert(std::make_pair(name, static_cast<GLuint>(i)));
        activeUniformList += std::string("\n") + name;
        //printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
    }
    std::cout << (activeUniformList);
}


GLuint RenderShader::GetUniformID(const std::string& name)
{
	const auto id = uniformMap.find(name);
#ifdef _DEBUG
    if (id == uniformMap.end())
    {
        std::cout << (name + " :No such uniform name");
        return -1;
    }
#endif
    return id->second;
}
bool RenderShader::OnCreate()
{
    std::cout<<("Creating RenderShader");
   
    bool status;
    status = CompileAttach();
    if (status == false) return false;
    status = Link();
    if (status == false) return false;

    SetUniformLocations();
    
    return true;
}