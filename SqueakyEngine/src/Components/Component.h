#pragma once
class Component {
public:
	Component(Component* parent_) :parent(parent_), isCreated(false) {}
	virtual ~Component() = default;
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const = 0;
	virtual void RenderGui()=0;
	void SetParent(Component* actor) {
		parent = actor;
	}
	Component* GetParent() const {
		return parent;
	}
protected:
	Component* parent;

	bool isCreated;
};

