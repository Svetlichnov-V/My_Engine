#pragma once
#include <cassert>
#include <string>
#include <iostream>
#include <vector>
#include "Vector2f.h"
#include "Buns.h"
#include "Game_Object.h"

class Collider : public Component 
{
    std::vector<Vector2f> vertexs;
    GameObject* master;
public:
    Collider(std::vector<Vector2f> vertexs)
    {
        //std::cout << "Collider" << '\n';
        this->vertexs = vertexs;
    }

    Collider() {};
    
    void printVert()
    {
        for (int i = 0; i < vertexs.size(); i++)
        {
            std::cout << vertexs[i] << '\n';
        }
        std::cout << '\n';
    }

    void setMaster(GameObject* master)
    {
        this->master = master;
    }

    Vector2f getPositionVertex(int number)
    {
        assert(number < vertexs.size());
        return master->getPosition() + vertexs[number];
    }

    bool isCollide(Collider* coll)
    {
        for (int i = 0; i < vertexs.size() - 1; i++)
        {
            Vector2f firstVertex  = this->getPositionVertex(i);
            Vector2f secondVertex = this->getPositionVertex(i + 1);

            Vector2f vector = secondVertex - firstVertex;

            Vector2f guidingVector = Vector2f(vector.y, (-1) * vector.x);
            Vector2f startStraight = firstVertex;

            float 
        }
    }
};

