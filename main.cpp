//
// Created by mike on 6/21/2024.
//

#include "screen.h"
#include <valarray>

struct vec3
{
    float x,y,z;
};

struct connection
{
    int a,b;
};

void rotate(vec3& point, float x = 1, float y = 1, float z = 1)
{
    //radian
    float rad = 0;

    rad = x;
    point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
    point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

    rad = y;
    point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

    rad = z;
    point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
    point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;

}

void line(Screen& screen, float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy,dx);

    for(float i = 0; i < length; i++)
    {
        screen.pixel(
                    x1 + std::cos(angle) * i,
                    y1 + std::sin(angle) * i
                    );
    }
}

int main(int argc, char* argv[])
{
    Screen screen;

    std::vector<vec3> points {
            {160,120,0},
            {400,120,0},
            {400,360,0},
            {160,360,0},

            {160,120,240},
            {400,120,240},
            {400,360,240},
            {160,360,240}

    };

    std::vector<connection> connect
    {
            {0,4},
            {1,5},
            {2,6},
            {3,7},

            //front face of the cube
            {0,1},
            {1,2},
            {2,3},
            {3,0},

            //back face of the cube
            {4,5},
            {5,6},
            {6,7},
            {7,4}

    };
    //Calculate the center point
    vec3 center{0,0,0};
    for(auto& p : points)
    {
        center.x += p.x;
        center.y += p.y;
        center.z += p.z;
    }
    center.x /= points.size();
    center.y /= points.size();
    center.z /= points.size();

    while(true)
    {
        for(auto& p : points)
        {
           p.x -= center.x;
           p.y -= center.y;
           p.z -= center.z;
           rotate(p, 0.002, 0.001, 0.004);
           p.x += center.x;
           p.y += center.y;
           p.z += center.z;
           screen.pixel(p.x, p.y);
        }

        for(auto& conn:connect)
        {
            line(screen, points[conn.a].x,
                            points[conn.a].y,
                            points[conn.b].x,
                            points[conn.b].y);

        }
        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(20);
    }

    return 0;
}