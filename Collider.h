#pragma once
#include <cassert>
#include <string>
#include <iostream>
#include "Buns.h"

class Collider : public Component 
{
public:
    Collider()
    {
        std::cout << "Collider" << '\n';
        geometry = 9;
    }
    int geometry;
};

