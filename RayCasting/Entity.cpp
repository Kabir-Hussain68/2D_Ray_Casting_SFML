#include "Entity.h"

Entity::Entity( size_t id, const string& tag)
    : m_id(id)
    , m_tag(tag)
{}

bool Entity::isAlive() const
{
    return (m_alive);
}

const string& Entity::tag() const
{
    return m_tag;
}

const size_t Entity::getid() const
{
    return m_id;
}

void Entity::destroy()
{
    m_alive = false;
}



