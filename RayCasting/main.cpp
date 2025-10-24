#include <SFML/Graphics.hpp>
#include <iostream>
#include "EntityManager.h"
#include <cmath>
#include <algorithm>

struct point{
float x, y;
float T1;
bool valid = false;
point(){}
point(float ax, float ay)
    :x(ax),
    y(ay)
    {}
point(float ax, float ay, float T)
    :x(ax),
    y(ay),
    T1(T),
    valid(true)
    {}
};


struct ray{
point origin, direction;
ray(point ax, point ay)
    :origin(ax),
    direction(ay)
    {}
};

struct segment{
point start, end;
sf::Color color;
segment(point ax, point ay, sf::Color color = sf::Color::White)
    :start(ax),
    end(ay),
    color(color)
    {}
};

point get_intersection(ray& ray, const segment& segment)
{
    Vec2 r_p = {ray.origin.x, ray.origin.y};
    Vec2 r_d = {ray.direction.x - ray.origin.x, ray.direction.y - ray.origin.y};
    Vec2 s_p = {segment.start.x, segment.start.y};
    Vec2 s_d = {segment.end.x - segment.start.x, segment.end.y - segment.start.y};

    //Calculating Magnitude and Checking it unit vector
    float r_mag = r_d.magnitude();
    float s_mag = s_d.magnitude();
    if(r_d.x/r_mag == s_d.x/s_mag && r_d.y/r_mag == s_d.y/s_mag)
    {
        return point(0, 0, 0);
    }

    //Solving for T1 and T2
    float T2 = (r_d.x * (s_p.y - r_p.y) + r_d.y * (r_p.x - s_p.x)) /(s_d.x * r_d.y - s_d.y * r_d.x);
    float T1 = (s_p.x + s_d.x * T2 - r_p.x) / r_d.x;


    //-ve value means its in opposite direction
    if (T1 < 0)
    {
        return point(0, 0);
    }
    //+ve value means its ahead of the point
    if (T2 < 0 || T2 > 1)
    {
        return point(0, 0);
    }

    return point(r_p.x + r_d.x*T1, r_p.y + r_d.y*T1, T1);
}

int main()
{
    EntityManager m_entityManager;
    sf::RenderWindow window(sf::VideoMode(1200, 900), "2D_Ray_Casting");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    //Window.setMouseCursorGrabbed(true);
    vector<segment> segments;
    //Window (0, 0) to (800, 600)
    segments.push_back(segment(point(0, 0), point(800, 0), sf::Color::White));     // Top edge
    segments.push_back(segment(point(800, 0), point(800, 600), sf::Color::White)); // Right edge
    segments.push_back(segment(point(800, 600), point(0, 600), sf::Color::White)); // Bottom edge
    segments.push_back(segment(point(0, 600), point(0, 0), sf::Color::White));     // Left edge

    segments.push_back(segment(point(100, 100), point(250, 80), sf::Color::Green));
    segments.push_back(segment(point(250, 80), point(180, 250), sf::Color::Green));
    segments.push_back(segment(point(180, 250), point(100, 100), sf::Color::Green));

    // Shape 2: Irregular Pentagon (Top-right)
    segments.push_back(segment(point(550, 70), point(650, 90), sf::Color::Yellow));
    segments.push_back(segment(point(650, 90), point(700, 200), sf::Color::Yellow));
    segments.push_back(segment(point(700, 200), point(600, 240), sf::Color::Yellow));
    segments.push_back(segment(point(600, 240), point(520, 160), sf::Color::Yellow));
    segments.push_back(segment(point(520, 160), point(550, 70), sf::Color::Yellow));

    // Shape 3: Trapezoid (Center-left)
    segments.push_back(segment(point(180, 320), point(300, 300), sf::Color::Cyan));
    segments.push_back(segment(point(300, 300), point(340, 400), sf::Color::Cyan));
    segments.push_back(segment(point(340, 400), point(160, 420), sf::Color::Cyan));
    segments.push_back(segment(point(160, 420), point(180, 320), sf::Color::Cyan));

    // Shape 4: Rotated Rectangle (Bottom-right)
    segments.push_back(segment(point(550, 400), point(700, 420), sf::Color::Magenta));
    segments.push_back(segment(point(700, 420), point(680, 540), sf::Color::Magenta));
    segments.push_back(segment(point(680, 540), point(530, 520), sf::Color::Magenta));
    segments.push_back(segment(point(530, 520), point(550, 400), sf::Color::Magenta));

    // Shape 5: L-shaped (Bottom-left)
    segments.push_back(segment(point(100, 500), point(180, 500), sf::Color::Blue));
    segments.push_back(segment(point(180, 500), point(180, 580), sf::Color::Blue));
    segments.push_back(segment(point(180, 580), point(140, 580), sf::Color::Blue));
    segments.push_back(segment(point(140, 580), point(140, 540), sf::Color::Blue));
    segments.push_back(segment(point(140, 540), point(100, 540), sf::Color::Blue));
    segments.push_back(segment(point(100, 540), point(100, 500), sf::Color::Blue));

    // Shape 6: Fat diamond (Center)
    segments.push_back(segment(point(400, 250), point(500, 300), sf::Color::Red));
    segments.push_back(segment(point(500, 300), point(400, 350), sf::Color::Red));
    segments.push_back(segment(point(400, 350), point(300, 300), sf::Color::Red));
    segments.push_back(segment(point(300, 300), point(400, 250), sf::Color::Red));


    sf::VertexArray lines(sf::Lines);
    for (const auto& seg : segments)
    {
        lines.append(sf::Vertex(sf::Vector2f(seg.start.x, seg.start.y), seg.color));
        lines.append(sf::Vertex(sf::Vector2f(seg.end.x, seg.end.y), seg.color));
    }

    //For Rays
    vector<point> litPoints;
    vector<point> uniquePoints;

    point prev_intersection;

    for(auto& seg : segments)
    {
        uniquePoints.push_back(seg.start);
        uniquePoints.push_back(seg.end);
    }

    //Mouse Player
    auto player = m_entityManager.addEntity("play");
    player->cShape = make_shared<CShape>(30, 30, sf::Color(255, 255, 0), sf::Color(255, 255, 0), 0);
    player->cTransform = make_shared<CTransform>(Vec2(400, 300), Vec2(5, 5), 0);
    player->cShape->circle.setPosition(player->cTransform->pos.x, player->cTransform->pos.y);

    m_entityManager.update();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            player->cTransform->pos.x = mouse.x;
            player->cTransform->pos.y = mouse.y;
            player->cShape->circle.setPosition(mouse.x, mouse.y);
        }

        //Calculating angle
        std::vector<float> uniqueAngles;
        for (const auto& p : uniquePoints)
        {
            float angle = std::atan2(p.y - player->cTransform->pos.y, p.x - player->cTransform->pos.x);
            uniqueAngles.push_back(angle - 0.00001f);
            uniqueAngles.push_back(angle);
            uniqueAngles.push_back(angle + 0.00001f);
        }
        std::sort(uniqueAngles.begin(), uniqueAngles.end());

        window.clear();

        //Drawing Lines
        window.draw(lines);

        point playerPos(player->cTransform->pos.x, player->cTransform->pos.y);

        // Create ray from player to mouse
        for (auto& p : uniqueAngles)
        {
            float dx = std::cos(p) * 10.0f;
            float dy = std::sin(p) * 10.0f;
            point rayDirection(playerPos.x + dx, playerPos.y + dy);
            ray ray(playerPos, rayDirection);
            float closestDistance = std::numeric_limits<float>::max();
            point closestIntersection;

            for (const auto& seg : segments)
            {
                point intersection = get_intersection(ray, seg);
                if (intersection.valid && intersection.T1 < closestDistance)
                {
                    closestDistance = intersection.T1;
                    closestIntersection = intersection;
                }
            }

            if (closestIntersection.valid)
            {
                litPoints.push_back(closestIntersection);
            }
        }
        std::sort(litPoints.begin(), litPoints.end(), [&](const point& a, const point& b)
                  {
                      float angleA = std::atan2(a.y - playerPos.y, a.x - playerPos.x);
                      float angleB = std::atan2(b.y - playerPos.y, b.x - playerPos.x);
                      return angleA < angleB;
                  });

        sf::VertexArray lightFan(sf::TriangleFan);
        lightFan.append(sf::Vertex(sf::Vector2f(playerPos.x, playerPos.y), sf::Color::White));
        for (const auto& pt : litPoints)
        {
            lightFan.append(sf::Vertex(sf::Vector2f(pt.x, pt.y), sf::Color(255, 255, 255, 255)));
        }
        if (!litPoints.empty())
        {
            lightFan.append(sf::Vertex(sf::Vector2f(litPoints.front().x, litPoints.front().y), sf::Color(255, 255, 255, 255)));
        }
        window.draw(lightFan);

        for(auto e : m_entityManager.getEntities())
        {
            window.draw(e->cShape->circle);
        }

        window.display();
        litPoints.clear();
    }

    return 0;
}

