#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Vec2.h"
#include "Entity.h"

// Forward declaration of Entity class
class Entity;

// Type alias for a vector of shared_ptr<Entity>
using EntityVec = std::vector<std::shared_ptr<Entity>>;

class EntityManager
{
private:
    EntityVec m_entities;                   // Vector of all entities
    EntityVec m_entitiesToAdd;              // Vector of entities to be added
    std::map<std::string, EntityVec> m_entityMap;  // Map of tag -> entities with that tag
    unsigned int m_totalEntities = 0;       // Total number of entities created

public:
    // Constructor and destructor (if needed)
    EntityManager() = default;
    ~EntityManager() = default;

    // Entity management functions
    void update();
    void removeDeadEntities(EntityVec& vec);
    std::shared_ptr<Entity> addEntity(const std::string& tag);

    // Entity retrieval functions
    const EntityVec& getEntities();
    const EntityVec& getEntities(const std::string& tag);
};

