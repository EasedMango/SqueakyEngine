#pragma once
#include "Component.h"
#include <string>
class Mesh :
    public Component
{
private:
	std::string filename;


public:
	explicit Mesh(const std::string& filename_);
	~Mesh() override;
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void RenderGui() override;
	std::string GetFilename() const { return filename; }
};

