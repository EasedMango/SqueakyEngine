#pragma once
#include "Component.h"
#include <variant>
#include <vector>
struct OBB;
struct Sphere;

//#include "Physics/Geometry3D.h"
//#include "Physics/AABB.h"
class Collider :
    public Component
{
private:
    std::variant<OBB*, Sphere*> shape;

    struct Collision
    {
        Collider* col;
        
    };

    std::vector<Collider*> handles;
public:
    //template<class T>
    //ColliderMath(T* shape_) : shape(shape_),Component(nullptr)
    //{
    //    
    //};

    explicit Collider(OBB* shape_) : Component(nullptr), shape(shape_)
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

  //  template<typename T>


    std::variant<OBB*, Sphere*> GetShape() const { return shape; }
};
