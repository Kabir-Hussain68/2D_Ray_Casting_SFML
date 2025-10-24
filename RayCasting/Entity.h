#pragma once


#include <memory>
#include <string>
#include "Components.h"

using namespace std;

class Entity
{
    friend class EntityManager;

    bool m_alive = true;
    size_t m_id = 0;
    string m_tag = "default";

    Entity (size_t id, const string& tag);

public:

    //Component Pointers
    shared_ptr<CTransform> cTransform;
    shared_ptr<CShape> cShape;
    shared_ptr<CCollision> cCollision;
    shared_ptr<CInput> cInput;

    //Access functions to members
    bool isAlive() const;
    const string& tag() const;
    const size_t getid() const;
    void destroy();
};

