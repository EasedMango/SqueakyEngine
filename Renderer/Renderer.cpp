#include "Renderer.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "RenderCamera.h"
#include "RenderTexture.h"
#include "RenderMesh.h"
#include "RenderShader.h"
#include <glm/gtx/string_cast.hpp>

#include "RenderSkybox.h"
#include "Text.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>




Renderer::Renderer()
{
	for (char y = 'A'; y <= 'Z'; ++y) {

		std::string w = "src/Meshes/Text/";
		std::string j(1, y);
		std::string z = w + j + std::string("1.obj");
		std::cout << z << " is the chars\n";
		std::cout << static_cast<int>(y) << std::endl;

		letters[y - 65] = new RenderMesh(z);

	}
	letterShader = CreateShader("phong");
}




Renderer::~Renderer()
= default;


RenderMesh* Renderer::CreateMesh(const std::string& filename)
{
	if (!meshes.contains(filename))
		return (meshes.at(filename).get());
	return nullptr;
}

RenderMesh* Renderer::GetMesh(const std::string& filename) const
{
	if (meshes.contains(filename))
		return (meshes.at(filename).get());
	return nullptr;
}

RenderMesh* Renderer::GetCreateMesh(const std::string& filename)
{
	if (meshes.contains(filename))
		return (meshes.at(filename).get());
	return meshes.emplace(filename, std::make_unique<RenderMesh>(filename)).first->second.get();
}

RenderTexture* Renderer::GetMaterial(const std::string& filename) const
{

	if (textures.contains(filename))
		return (textures.at(filename).get());
	return nullptr;
}

RenderTexture* Renderer::CreateMaterial(const std::string& filename)
{
	if (!meshes.contains(filename)) {
		
		RenderTexture* temp= textures.emplace(filename, std::make_unique<RenderTexture>(filename)).first->second.get();
		temp->OnCreate();
		return temp;
	}
	return nullptr;
}


RenderTexture* Renderer::GetCreateMaterial(const std::string& filename)
{
	if (textures.contains(filename))
		return (textures.at(filename).get());

	RenderTexture* temp = textures.emplace(filename, std::make_unique<RenderTexture>(filename)).first->second.get();
	temp->OnCreate();
	return temp;
}

RenderShader* Renderer::GetShader(const std::string& filename) const
{
	if (shaders.contains(filename))
		return (shaders.at(filename).get());
	return nullptr;
}

RenderShader* Renderer::CreateShader(const std::string& filename)
{
	RenderShader* temp = shaders.emplace(filename, std::make_unique<RenderShader>(filename)).first->second.get();
	temp->OnCreate();
	return temp;
}



RenderShader* Renderer::GetCreateShader(const std::string& filename)
{
	if (shaders.contains(filename))
		return (shaders.at(filename).get());


	RenderShader* temp = shaders.emplace(filename, std::make_unique<RenderShader>(filename)).first->second.get();
	temp->OnCreate();
	return temp;
}

RenderSkybox* Renderer::CreateSkybox(const std::string& posXFile_, const std::string& posYFile_,
	const std::string& posZFile_, const std::string& negXFile_,
	const std::string& negYFile_, const std::string& negZFile_)
{
	/*const auto newShader = std::make_unique<RenderSkybox>(posXFile_, posYFile_, posZFile_, negXFile_, negYFile_, negZFile_);*/
	RenderSkybox* temp = skyboxes.emplace(posXFile_, std::make_unique<RenderSkybox>(posXFile_, posYFile_, posZFile_, negXFile_, negYFile_, negZFile_)).first->second.get();
	temp->OnCreate();
	activeSkybox = temp;
	return temp;

	return activeSkybox;
}
RenderSkybox* Renderer::GetSkybox(const std::string& filename) const
{
	if (skyboxes.contains(filename))
		return (skyboxes.at(filename).get());
	return nullptr;
}
RenderSkybox* Renderer::GetCreateSkybox(const std::string& posXFile_, const std::string& posYFile_,
	const std::string& posZFile_, const std::string& negXFile_,
	const std::string& negYFile_,
	const std::string& negZFile_)
{
	RenderSkybox* rm = GetSkybox(posXFile_);
	if (rm == nullptr)
	{
		return CreateSkybox(posXFile_, posYFile_, posZFile_, negXFile_, negYFile_, negZFile_);
	}

	return rm;
}
void Renderer::DrawSphere(const glm::vec3& pos)
{
	AddToQueue("default", "src/Meshes/Sphere.obj", "White.png", glm::translate(glm::mat4(1), pos));
}


void Renderer::SetCamera( RenderCamera* cam)
{
	camera = cam;
}


void Renderer::LoadShader(RenderShader* shader) const
{
	glUseProgram(shader->GetProgram());
	camera->SendUniforms(shader);
}

bool Renderer::MeshRender(const RenderObject& object)
{
	//glEnable(GL_CULL_FACE);
	bool emp = activeShader != nullptr;
	if (emp)
	{
		emp = (object.shader == activeShader->GetFileName());
	}
	else
	{
		activeShader = GetCreateShader(object.shader);
		if (activeShader == nullptr)
		{
			std::cout << "no shader found or created\n";
			exit(0);
		}

		emp = true;
	}
	if (emp)
	{
		LoadShader(activeShader);
		const RenderTexture* mat = GetCreateMaterial(object.texture);


		const RenderMesh* mesh = GetCreateMesh(object.mesh);

		glUniform3fv(activeShader->GetUniformID("lightPos"), 1, glm::value_ptr(glm::vec3(0,0,0) ));
		glUniformMatrix4fv(activeShader->GetUniformID("modelMatrix"), 1, GL_FALSE,
			value_ptr(object.matrix));

		if (mat != nullptr && mat->GetFileName() != "White.png")
			glBindTexture(GL_TEXTURE_2D, GetMaterial(object.texture)->GetTextureID());
		else
			glBindTexture(GL_TEXTURE_2D, 0);
		mesh->Render();
		glBindTexture(GL_TEXTURE_2D, 0);
		//glUseProgram(0);
		return true;
	}

	return false;
}

bool Renderer::SkyboxRender(const RenderSkybox& skybox)
{
	if (activeSkybox == nullptr)
		return false;
	if (activeShader == nullptr)
		activeShader = GetCreateShader("skybox");

	LoadShader(activeShader);

	//glm::mat4 view = camera->GetViewMatrix();
	//view[3].x = 0;
	//view[3].y = 0;
	//view[3].z = 0;
	////std::cout << glm::to_string(view) << std::endl;

	//glUniformMatrix4fv(activeShader->GetUniformID("viewMatrix"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(activeShader->GetUniformID("modelMatrix"), 1, GL_FALSE,
		value_ptr(glm::mat4(1)));
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);


	glBindTexture(GL_TEXTURE_CUBE_MAP, GetSkybox(activeSkybox->GetFilename())->GetTextureID());
	GetCreateMesh("src/Meshes/Cube.obj")->Render();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	return true;
}

void Renderer::Render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SkyboxRender(*activeSkybox);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	while (!tempQueue.empty() || !renderQueue.empty())
	{
		activeShader = nullptr;
		while (!renderQueue.empty())
		{
			if (!MeshRender(renderQueue.front()))
			{
				tempQueue.emplace(renderQueue.front());
			}
			renderQueue.pop();
		}
		activeShader = nullptr;
		while (!tempQueue.empty())
		{
			if (!MeshRender(tempQueue.front()))
			{
				renderQueue.emplace(tempQueue.front());
			}
			tempQueue.pop();
		}
	}
	while (!textQueue.empty())
	{
		RenderText(textQueue.front());
		textQueue.pop();
	}
	glUseProgram(0);
}

void Renderer::AddToQueue(const std::string& shader, const std::string& mesh_,
	const std::string& material_, const glm::mat4& modelMatrix)
{
	renderQueue.emplace(RenderObject{ shader,  mesh_, material_, modelMatrix });
}

void Renderer::UpdateCamera(const glm::mat4 view) const
{
	camera->UpdateViewMatrix();
}

void Renderer::AddText(const Text& t)
{
	textQueue.emplace(t);
}



void Renderer::RenderText(const Text& text_)
{
	const glm::mat4 modelMatrix = (glm::mat4(1));// , text_.position);
	glm::mat4 view = camera->GetViewMatrix();
	//view[3].x = 0;
	//view[3].y = 0;
	//view[3].z = 0;


	LoadShader(letterShader);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	///glUseProgram(letterShader->GetProgram());
	LoadShader(letterShader);
	//glUniformMatrix4fv(letterShader->GetUniformID("projectionMatrix"), 1, GL_FALSE,
	//	glm::value_ptr(camera->GetProjectionMatrix()));
	//glUniformMatrix4fv(letterShader->GetUniformID("viewMatrix"), 1, GL_FALSE, glm::value_ptr(view));

	glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE,
		glm::value_ptr(modelMatrix));
	//origin->Render(GL_TRIANGLES);

	float lPos = 0;
	glBindTexture(GL_TEXTURE_2D, GetCreateMaterial((std::string("mario_fire.png")))->GetTextureID());




	for (int x = 0; x < text_.text.size(); ++x) {
		//std::cout << int(text_.text[x]) << "\n";
		switch (static_cast<int>(text_.text[x]) - 97)
		{
		case 0:
			//std::cout << "the letter is a\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;

			break;
		case 1:
			//	std::cout << "the letter is b\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 2:
			//	std::cout << "the letter is c\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 3:
			//	std::cout << "the letter is d\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 4:
			//	std::cout << "the letter is e\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 5:
			//	std::cout << "the letter is f\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 6:
			//	std::cout << "the letter is g\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 7:
			//	std::cout << "the letter is h\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 8:
			//	std::cout << "the letter is i\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 9:
			//	std::cout << "the letter is j\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 10:
			//	std::cout << "the letter is k\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 11:
			//	std::cout << "the letter is l\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 12:
			//	std::cout << "the letter is m\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 13:
			//	std::cout << "the letter is n\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 14:
			//	std::cout << "the letter is o\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 15:
			//	std::cout << "the letter is p\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 16:
			//	std::cout << "the letter is q\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 17:
			//	std::cout << "the letter is r\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 18:
			//	std::cout << "the letter is s\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 19:
			//	std::cout << "the letter is t\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 20:
			//	std::cout << "the letter is u\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 21:
			//	std::cout << "the letter is v\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 22:
			//	std::cout << "the letter is w\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 23:
			//	std::cout << "the letter is x\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 24:
			//	std::cout << "the letter is y\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		case 25:
			//	std::cout << "the letter is z\n";
			glUniformMatrix4fv(letterShader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix * glm::translate(glm::mat4x4(1), glm::vec3(lPos, 0, 0)) * glm::rotate(glm::mat4x4(1), 90.0f, glm::vec3(1, 0, 0)) * glm::scale(glm::mat4x4(1), glm::vec3(text_.fontSize, text_.fontSize, text_.fontSize))));
			letters[static_cast<int>(text_.text[x]) - 97]->Render();
			lPos++;
			break;
		default:
			lPos++;
			break;
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);



}