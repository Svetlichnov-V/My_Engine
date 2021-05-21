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
    Vector2f size;
    Vector2f centerMass;
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

    void setSize(Vector2f s)
    {
        size = s;
    }

    Vector2f getSize()
    {
        return size;
    }

    Vector2f getPositionVertex(int number)
    {
        assert(number < vertexs.size());
        return master->getPosition() + vertexs[number];
    }

    int getNumberOfVertex()
    {
        return vertexs.size();
    }

    Vector2f getVertex(int number)
    {
        assert(number < vertexs.size());
        return vertexs[number];
    }

    Vector2f getCenterMass()
    {
        return centerMass;
    }

    void setCenterMass(Vector2f cm)
    {
        centerMass = cm;
    }

    Vector2f getInwardNormal(int numberVertex)
    {
        Vector2f v(0, 0);
        if (numberVertex == 0)
            v = this->getVertex(vertexs.size() - 1) - this->getVertex(1);
        if (numberVertex == (vertexs.size() - 1))
            v = this->getVertex(0) - this->getVertex(numberVertex - 1);
        if ((numberVertex != 0) && (numberVertex != (vertexs.size() - 1)))
            v = this->getVertex(numberVertex - 1) - this->getVertex(numberVertex + 1);

        Vector2f d(v.y, -v.x);
        Vector2f a = this->getVertex(numberVertex) - centerMass;
        return ((a * d) * d * (-1)).norm();
    }

    Vector2f isCollide(Collider* coll)
    {
        /*
        for (int i = 0; i < vertexs.size() - 1; i++)
        {
            Vector2f firstVertex = this->getPositionVertex(i);
            Vector2f secondVertex = this->getPositionVertex(i + 1);

            Vector2f vector = secondVertex - firstVertex;

            Vector2f guidingVector = Vector2f(vector.y, (-1) * vector.x);
            Vector2f startStraight = firstVertex;

            float
        };  
        */

        Vector2f position     = this->master->getPosition();
        Vector2f gObjPosition = coll->master->getPosition();

        if ((position - gObjPosition).mod() > (size + coll->getSize()).mod())
            return Vector2f(0, 0);
        int gObjNumberOfVertexs = coll->getNumberOfVertex();
        if (gObjNumberOfVertexs < 2)
            return Vector2f(0, 0);

        Vector2f vectorCollision(0, 0);

        int numberOfVertexs = vertexs.size();

        for (int numberVertex = 0; numberVertex < numberOfVertexs; numberVertex++)
        {
            bool flag = true;
            for (int numberGObjvertex = 1; numberGObjvertex < gObjNumberOfVertexs; numberGObjvertex++)
            {
                //std::cout << gObj.name << '\n';
                Vector2f v1 = coll->getPositionVertex(numberGObjvertex) - coll->getPositionVertex(numberGObjvertex - 1);
                Vector2f v2 = this->getPositionVertex(numberVertex)     - coll->getPositionVertex(numberGObjvertex - 1);

                //std::cout << numberVertex << ' ' << numberGObjvertex << " : " << v1 << " ; " << v2 << '\n';

                if (v1.vectComp(v2) > 0)
                {
                    flag = false;
                    break;
                }
            }
            Vector2f v1 = coll->getPositionVertex(0)            - coll->getPositionVertex(gObjNumberOfVertexs - 1);
            Vector2f v2 = this->getPositionVertex(numberVertex) - coll->getPositionVertex(gObjNumberOfVertexs - 1);

            if (v1.vectComp(v2) > 0)
            {
                continue;
            }

            if (flag)
            {
                //std::cout << (this->getVertex(numberVertex) - centerMass) << '\n';
                vectorCollision += this->getInwardNormal(numberVertex);
            }
        }

        if (vectorCollision.mod() == 0)
            return vectorCollision;

        return vectorCollision.norm();
    }
};

