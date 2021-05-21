#pragma once
#include <unordered_map>
#include "Renderer.h"
#include "Collider.h"
#include "Buns.h"
#include "Vector2f.h"


class GameObject
{
	std::unordered_map<std::string, Component*> components;
    Vector2f position;

public:
    template <typename T>
    T* GetComponent()
    {
        //std::cout << "GetComponent" << '\n';
        return static_cast<T*>(components[typeid(T).name()]);
    };

    template <class T>
    void AddComponent(T component)
    {
        //std::cout << "AddComponent" << '\n';
        T* comp = new T();
        *comp = component;
        Component* c = comp;
        components[typeid(T).name()] = c;
    };

    template <class T>
    void AddComponentWithoutContent(T component)
    {
        //std::cout << "AddComponentWithoutContent" << '\n';
        components[typeid(T).name()] = new T();
    };

    void setPosition(Vector2f pos)
    {
        position = pos;
    }

    Vector2f getPosition()
    {
        return position;
    }

    ~GameObject()
    {
        std::unordered_map<std::string, Component*>::iterator it;
        it = components.begin();
        while (it != components.end())
        {
            //delete it->second;
            it++;
        }
    }

    Vector2f getPosition()
    {
        return position;
    }
    //RemoveComponent
};