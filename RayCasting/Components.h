#pragma once


#include "Vec2.h"
#include <SFML/Graphics.hpp>

class CTransform
{
public:
    Vec2 pos = {0.0f, 0.0f};
    Vec2 velocity = {0.0f, 0.0f};
    float angle = 0;

    CTransform(const Vec2& p, const Vec2& v, const float a)
        :pos(p), velocity(v), angle(a)
    {
    }
};

class CShape
{
public:
    sf::CircleShape circle;
    int pointCount;

    CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
        :circle(radius, points), pointCount(points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(sf::Vector2f(radius, radius));
    }
};

class CInput
{
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    CInput()
    {

    }
};

class CCollision
{
public:
    float radius = 0;
    CCollision(float r)
        :radius(r)
    {}
};



