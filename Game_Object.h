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
    T* GetComponent(std::string key)
    {
        Component* component = components[key];
        if (typeid(*component) != T)
            assert();
        static_cast<T*>(component);
        // static cast

        // typeid()

        return component;
    };

    template <typename T>
    void AddComponent(std::string key, T component)
    {
        T* comp = new T();
        *comp = component;
        Component* c = comp;
        components.insert({ key, c });
    };

    //RemoveComponent
};