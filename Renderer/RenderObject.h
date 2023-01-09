#pragma once

//psuedo interface/base class for rendering objects
class RenderObject
{
private:
	friend class Renderer;

	int priority;

public:
	RenderObject() = default;
	virtual ~RenderObject() = default;

	virtual void Render();

	
};

