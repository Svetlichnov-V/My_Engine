#pragma once
#include "Game_Object.h"

void graphics(GameObject obj)
{
    Renderer* r = obj.GetComponent<Renderer>("Renderer");
}

int main()
{
    GameObject obj;

    Renderer rend();
    Collider coll();
    obj.AddComponent<Renderer>("Renderer", rend);
    obj.AddComponent<Collider>("Collider", coll);

    graphics(obj);
}