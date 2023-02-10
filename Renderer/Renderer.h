#pragma once
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <glad/glad.h>

#include "glm/matrix.hpp"
#include <queue>
#include "Text.h"
#include <unordered_map>

class RenderSkybox;
class RenderCamera;
class RenderShader;
class RenderTexture;
class RenderMesh;
class RenderLight;
#define MAX_LIGHTS 12;

class Renderer
{
private:


	RenderMesh* letters[26]{};
	RenderShader* letterShader{};

	std::queue<Text> textQueue;
	
	struct RenderObject
	{
		std::string shader;
		std::string mesh;
		std::string texture;
		glm::mat4 matrix;
	};

	glm::vec3 position{};

	glm::vec3 color{};
	float attenuation{};


	std::unordered_map<std::string, std::unique_ptr<RenderMesh>> meshes;
	std::unordered_map<std::string, std::unique_ptr<RenderTexture>> textures;
	std::unordered_map<std::string, std::unique_ptr<RenderShader>> shaders;
	std::unordered_map<std::string, std::unique_ptr<RenderSkybox>> skyboxes;
	RenderCamera* camera{};
	RenderShader* activeShader{};
	RenderSkybox* activeSkybox{};
	std::queue<RenderObject> renderQueue;
	std::queue<RenderObject> tempQueue;
	GLuint LightUniformBuffer{};
	//static Renderer *render;
	~Renderer();

	//Material Getters and Setters 
	RenderTexture* CreateMaterial(const std::string& filename);
	RenderTexture* GetMaterial(const std::string& filename) const;

	//Shader Getters and Setters 
	RenderShader* CreateShader(const std::string& filename);
	RenderShader* GetShader(const std::string& filename) const;

	//Mesh Getters and Setters 
	RenderMesh* CreateMesh(const std::string& filename);
	RenderMesh* GetMesh(const std::string& filename) const;

	//Skybox Getters and Setters 
	RenderSkybox* CreateSkybox(
		const std::string& posXFile_, const std::string& posYFile_, const std::string& posZFile_,
		const std::string& negXFile_, const std::string& negYFile_, const std::string& negZFile_);
	RenderSkybox* GetSkybox(const std::string& filename) const;



	//Tells gpu to use given shader
	void LoadShader(RenderShader* shader) const;


	//Tells gpu to render the parameters inside RenderObject
	bool MeshRender(const RenderObject& object);

	bool SkyboxRender(const RenderSkybox& skybox);
	void RenderText(const class Text& text_);
public:

	//keep only single instance of renderer 
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	void DrawSphere(const glm::vec3& pos);
	//Get Renderer
	static Renderer& GetInstance()
	{
		// Allocate with `new` in case Singleton is not trivially destructible.
		static auto singleton = new Renderer();
		return *singleton;
	}


	//sets the camera
	void SetCamera( RenderCamera* cam);


	/**
	 * \brief Tries to get Material if it exists. Else will try to create Material. If both fail it returns a nullptr
	 * \param filename filename and location of the texture
	 * \return RenderMaterial Pointer
	 */
	RenderTexture* GetCreateMaterial(const std::string& filename);


	/**
	 * \brief Tries to get Shader if it exists. Else will try to create Shader. If both fail it returns a nullptr
	 * \param filename filename and location of the Shader
	 * \return RenderShader Pointer
	 */
	RenderShader* GetCreateShader(const std::string& filename);


	/**
	* \brief Tries to get Mesh if it exists. Else will try to create Mesh. If both fail it returns a nullptr
	* \param filename filename and location of the texture
	* \return RenderMesh Pointer
	*/
	RenderMesh* GetCreateMesh(const std::string& filename);


	RenderSkybox* GetCreateSkybox(
		const std::string& posXFile_, const std::string& posYFile_ = std::string(""),
		const std::string& posZFile_ = std::string(""), const std::string& negXFile_ = std::string(""),
		const std::string& negYFile_ = std::string(""), const std::string& negZFile_ = std::string(""));


	//Render loop for handles the Queues 
	void Render();

	/* Creates and Adds renderObject to queue */
	void AddToQueue(const std::string& shader, const std::string& mesh_, const std::string& material_, const glm::mat4& modelMatrix);



	//updates Camera Position 
	void UpdateCamera(glm::mat4 view) const;

	void AddText(const Text& t);
};
