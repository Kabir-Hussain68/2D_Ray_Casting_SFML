#include "Vec2.h"
#include<math.h>

Vec2::Vec2()
{

}

Vec2::Vec2(float xin, float yin)
    :x(xin), y(yin)
{
}

Vec2 Vec2::operator + (const Vec2& rhs)const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs)const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2:: operator * (const float val)const
{
    return Vec2(x * val, y * val);
}

Vec2 Vec2:: operator / (const float val)const
{
    return Vec2(x / val, y / val);
}

bool Vec2::operator == (const Vec2& rhs)const
{
    return (x == rhs.x, y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs)const
{
    return (x != rhs.x, y != rhs.y);
}

void Vec2::operator += (const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator *= (const float val)
{
    x *= val;
    y *= val;
}

void Vec2::operator /= (const float val)
{
    x /= val;
    y /= val;
}

//TODO
float Vec2::dist(const Vec2& rhs)const
{
    Vec2 D = {x - rhs.x, y - rhs.y};
    return std::sqrt (D.x*D.x + D.y*D.y);
}

float Vec2::magnitude() const
{
    return std::sqrt(x*x + y*y);
}

Vec2 Vec2::normalize() const
{
    float length = std::sqrt(x * x + y * y);
    if (length != 0)
        return Vec2(x / length, y / length);
    else
        return Vec2(0, 0);
}

