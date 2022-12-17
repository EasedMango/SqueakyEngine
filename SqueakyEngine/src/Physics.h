#pragma once
#include <vector>
#include "Components/PhysicsBody.h"
#include <map>

/**
 * \brief Base class for physics engine, 
 */
class Physics
{
private:
    std::vector<PhysicsBody*> bodies;
    int physicsBodies;
    //std::map<std::string, PhysicsBody*> bodies;
    //std::vector< std::string, PhysicsBody*> bodies;
public:
    struct Rayhit
    {
         class Actor* actor;
         glm::vec3 point;
         glm::vec3 normal;
         float distance;
        Rayhit() : actor(nullptr),point(0.f),normal(0.f),distance(0.f)
        {
	        
        }
    };
    Physics()
    = default;

     bool Raycast(const glm::vec3& pos, const glm::vec3& dir,  Rayhit& rayhit) const;
    
    void AddBody(PhysicsBody* body);

    std::vector<PhysicsBody*> ReturnBodies()
    {
        return bodies;
    }

    void Update(float deltaTime) const;

    void RemoveBody(PhysicsBody* pb);

    void OnDestroy();


    static void RenderGui();
};

