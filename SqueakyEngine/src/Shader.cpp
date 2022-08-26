#include "Shader.h"
#include <fstream>
#include <string.h>
#include "Logger.h"


bool Shader::CompileShader(GLuint& id, const char* fileName, GLint status =0)
{
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        GLsizei errorLogSize = 0;
        GLsizei titleLength;
        std::string errorLog = fileName;
        errorLog += ":\n";
        titleLength = errorLog.length();
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errorLogSize);
        errorLog.resize(titleLength + errorLogSize);
        glGetShaderInfoLog(id, errorLogSize, &errorLogSize, &errorLog[titleLength]);
        throw errorLog;
    }
    
    return true;
}

bool Shader::CompileAttach()
{
    GLint status;
    try {
        const char* vsText = ReadTextFile(vsFilename);
        const char* fsText = ReadTextFile(fsFilename);
        vertShaderID = glCreateShader(GL_VERTEX_SHADER);
        fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vertShaderID, 1, &vsText, NULL);
        glShaderSource(fragShaderID, 1, &fsText, NULL);

        glCompileShader(vertShaderID);
        /// Check for errors
        glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &status);
        if (status == 0) {
            GLsizei errorLogSize = 0;
            GLsizei titleLength;
            std::string errorLog = vsFilename;
            errorLog += "\nVERT:\n";
            titleLength = errorLog.length();
            glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
            errorLog.resize(titleLength + errorLogSize);
            glGetShaderInfoLog(vertShaderID, errorLogSize, &errorLogSize, &errorLog[titleLength]);
            throw errorLog;
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;
        glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(vertShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }

        glCompileShader(fragShaderID);
        /// Check for errors
        glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &status);
        if (status == 0) {
            GLsizei errorLogSize = 0;
            GLsizei titleLength;
            std::string errorLog = fsFilename;
            errorLog += "\nFrag:\n";
            titleLength = errorLog.length();
            glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
            errorLog.resize(titleLength + errorLogSize);
            glGetShaderInfoLog(fragShaderID, errorLogSize, &errorLogSize, &errorLog[titleLength]);
            throw errorLog;
        }
        glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(fragShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }
        shaderID = glCreateProgram();
        glAttachShader(shaderID, vertShaderID);
        glAttachShader(shaderID, fragShaderID);
        if (vsText) delete[] vsText;
        if (fsText) delete[] fsText;
    }
    catch (std::string error) {
        printf("%s\n", &error[0]);
        Logger::Error(error);
        return false;
    }
    return true;
}

bool Shader::Link()
{
    GLint Result = GL_FALSE;
    int InfoLogLength;
    GLint status;
    try {
        glLinkProgram(shaderID);
        /// Check for errors
        glGetProgramiv(shaderID, GL_LINK_STATUS, &status);
        GLsizei errorLogSize = 0;
        std::string errorLog;
        glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
        errorLog.resize(errorLogSize);
        glGetProgramInfoLog(shaderID, errorLogSize, &errorLogSize, &errorLog[0]);
        Logger::Info(errorLog);
        glGetProgramiv(shaderID, GL_LINK_STATUS, &Result);
        glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
            glGetProgramInfoLog(shaderID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }
        if (status == 0) {

            throw errorLog;
        }

    }
    catch (std::string error) {
        Logger::Error(error);
        return false;
    }
    return true;
}

//gets uniform names and locations from shaderProgram/shaderID
void Shader::SetUniformLocations()
{
    int count;
    GLsizei actualLen;
    GLint size;
    GLenum type;
    char* name;
    int maxUniformListLength;
    unsigned int loc;
    char buffer[512];

    std::string activeUniformList = "Uniforms:\n";
    glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &count);
    sprintf_s(buffer, 512, "There are %d active Uniforms\n", count);

    /// get the length of the longest named uniform 
    glGetProgramiv(shaderID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformListLength);

    /// Create a little buffer to hold the uniform's name - old C memory call just for fun 
    name = (char*)malloc(sizeof(char) * maxUniformListLength);


    for (int i = 0; i < count; ++i) {

        /// Get the name of the ith uniform

        glGetActiveUniform(shaderID, i, maxUniformListLength, &actualLen, &size, &type, name);
        /// Get the (unsigned int) loc for this uniform
        loc = glGetUniformLocation(shaderID, name);
        std::string uniformName = name;
        uniformMap[uniformName] = loc;

        sprintf_s(buffer, 512, "\"%s\" loc:%d\n", uniformName.c_str(), uniformMap[uniformName]);
        activeUniformList += buffer;
    }
    Logger::Info(activeUniformList);
    free(name);
}

Shader::Shader(Component* parent_, const char* vsFilename_, const char* fsFilename_) :
    Component(parent_),
    shaderID(0), vertShaderID(0), fragShaderID(0) 
{
    vsFilename = vsFilename_;
    fsFilename = fsFilename_;
}

Shader::~Shader()
{
}

/// Read from a specified file and return a char array from the heap 
/// The memory must be deleted within this class. It may not be the best way 
/// to do this but it is all private and I did delete it! SSF
char* Shader::ReadTextFile(const char* filename) {
    char* buffer = nullptr;
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {								/// Open the file
        file.seekg(0, std::ios::end);					/// goto the end of the file
        int bufferSize = (int)file.tellg();			/// Get the length of the file
        if (bufferSize == 0) {							/// If zero, bad file
            std::string errorMsg("Can't read shader file: ");
            std::string str2(filename);
            errorMsg += str2;
            throw errorMsg;								/// Bail out
        }
        buffer = new char[(int)(bufferSize + 1)];		/// Need to NULL terminate the array
        file.seekg(0, std::ios::beg);
        file.read(buffer, bufferSize);
        buffer[bufferSize] = NULL;						/// Add the NULL
        file.close();
    }
    else {
        std::string errorMsg("Can't open shader file: ");
        errorMsg += filename;
        Logger::Error(errorMsg);
    }
    return buffer;
}

GLuint Shader::GetUniformID(std::string name)
{
    auto id = uniformMap.find(name);
#ifdef _DEBUG
    if (id == uniformMap.end()) {
        Logger::Error(name + " :No such uniform name");
        return -1;
    }
#endif 
    return id->second;
}

bool Shader::OnCreate()
{
    if (isCreated) return true;
    bool status;
    status = CompileAttach();
    if (status == false) return false;
    status = Link();
    if (status == false) return false;

    SetUniformLocations();
    isCreated = true;
    return true;
}

void Shader::OnDestroy()
{
    glDetachShader(shaderID, fragShaderID);
    glDetachShader(shaderID, vertShaderID);
    glDeleteShader(fragShaderID);
    glDeleteShader(vertShaderID);
    glDeleteProgram(shaderID);
}

void Shader::Update(const float deltaTime)
{
}

void Shader::Render() const
{
    glUseProgram(GetProgram());
}
