#pragma once
#include <unordered_map>
#include "Renderer.h"
#include "Collider.h"
#include "Buns.h"


class GameObject
{
	std::unordered_map<std::string, Component*> components;

public:
    template <typename T>
    T* GetComponent()
    {
        //Component* component = components[key];
        //if (typeid(*component) != typeid(T))
        //    assert();
        //static_cast<T*>(component);
        // static cast

        // typeid()
        std::cout << "GetComponent" << '\n';
        return static_cast<T*>(components[typeid(T).name()]);
    };

    template <class T>
    void AddComponent(T component)
    {
        std::cout << "AddComponent" << '\n';
        T* comp = new T();
        *comp = component;
        Component* c = comp;
        components[typeid(T).name()] = c;
        //(*components[typeid(T).name()]) = component;
    };

    //RemoveComponent
};