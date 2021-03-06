#pragma once
#include "Game_Object.h"

void graphics(GameObject obj)
{
    Renderer* r = obj.GetComponent<Renderer>();
    std::cout << r->sprite << '\n';
}

int main()
{
    GameObject obj;

    Renderer rend;
    rend.sprite = 10;
    std::vector<Vector2f> vertexs = { {10, 5}, {5, 10} };
    Collider coll(vertexs);

    obj.AddComponent<Renderer>(rend);
    obj.AddComponent<Collider>(coll);

    Collider* c = obj.GetComponent<Collider>();
    c->printVert();
    //graphics(obj);

}