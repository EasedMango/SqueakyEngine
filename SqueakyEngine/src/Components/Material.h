#pragma once
#include "Component.h"
#include <string>

class Material :
    public Component
{
public:

private:
	std::string filename;


public:
	 Material( const std::string& filename);

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void RenderGui() override;
	std::string GetFilename() const;
	~Material() override;
};

