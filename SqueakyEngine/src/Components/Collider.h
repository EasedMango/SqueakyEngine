#pragma once
#include "Component.h"
#include <variant>
#include <vector>
struct Sphere;
struct AABB;
//#include "Physics/Geometry3D.h"
//#include "Physics/AABB.h"
class Collider :
    public Component
{
private:
    std::variant<AABB*, Sphere*> shape;
    std::vector<Collider*> handles;
public:
    //template<class T>
    //ColliderMath(T* shape_) : shape(shape_),Component(nullptr)
    //{
    //    
    //};

    explicit Collider(AABB* shape_) : Component(nullptr), shape(shape_)
    {
    }

    explicit Collider(Sphere* shape_) : Component(nullptr), shape(shape_)
    {
    }
   

    Collider();
    ~Collider() override;

    void AddHandle(Collider* col) { handles.push_back(col); }

    void Update(float deltaTime) override;
    bool OnCreate() override;
    void OnDestroy() override;
    void Render() const override;
    void RenderGui() override;

    static void OnCollision();

    bool IsColliding(const Collider* col);
    void ClearHandles() { handles.clear(); }
    std::vector<Collider*> GetHandles() { return handles; }

    std::variant<AABB*, Sphere*> GetShape() const { return shape; }
};
