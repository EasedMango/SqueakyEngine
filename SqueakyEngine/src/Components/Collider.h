#pragma once
#include "Component.h"
#include <variant>
#include <vector>
//#include "Physics/Geometry3D.h"
#include "Physics/Geometry.h"
class Collider :
    public Component
{
private:
    std::variant<Geometry::AABB*, Geometry::Sphere*> shape;
    std::vector<Collider*> handles;
public:
    //template<class T>
    //Collider(T* shape_) : shape(shape_),Component(nullptr)
    //{
    //    
    //};

    explicit Collider(Geometry::AABB* shape_) : Component(nullptr), shape(shape_)
    {
    };

    explicit Collider(Geometry::Sphere* shape_) : Component(nullptr), shape(shape_)
    {
    };
   

    Collider();
    ~Collider() override;

    void AddHandle(Collider* col) { handles.push_back(col); }

    void Update(float deltaTime) override;
    bool OnCreate() override;
    void OnDestroy() override;
    void Render() const override;
    void RenderGui() override;

    void OnCollision();

    bool IsColliding(const Collider* col);
    void ClearHandles() { handles.clear(); }
    std::vector<Collider*> GetHandles() { return handles; }

    std::variant<Geometry::AABB*, Geometry::Sphere*> GetShape() const { return shape; }
};
