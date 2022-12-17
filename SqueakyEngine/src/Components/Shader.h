#pragma once
#include "Component.h"
#include <string>
class Shader :
    public Component
{
private:
	std::string filenameV;
	std::string filenameF;
public:
	Shader(const std::string& filenameV, const std::string& filenameF);
	inline std::string GetFilenameV() const { return filenameV; }
	inline std::string GetFilenameF() const { return filenameF; }
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void RenderGui() override;
	~Shader() override;
};

