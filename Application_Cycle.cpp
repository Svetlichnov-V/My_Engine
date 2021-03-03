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
    Collider coll;

    obj.AddComponent<Renderer>(rend);
    obj.AddComponent<Collider>(coll);

    graphics(obj);
}