#pragma once

#include"Component.h"
#include"Transform.h"
#include"Behaviour.h"
#include <vector>

class GameObject
{
public:
	template<typename T>T* AddComponent();

	template<typename T>T* GetComponent();

	template<typename T>T RemoveComponent();

	std::vector<Component*> components;
};



template<typename T>
inline T* GameObject::AddComponent()
{
	T* t = new T();
	//Componentクラスから派生したものかチェック
	Component* component = static_cast<Component*>(t);
	if (component != nullptr)
	{
		components.push_back(component);
		return t;
	}
}

template<typename T>
inline T* GameObject::GetComponent()
{
	for (int i = 0; i < (int)components.size(); i++)
	{
		T* component = dynamic_cast<T*>(components[i]);
		if (component != nullptr)
		{
			return component;
		}
	}
	return nullptr;
}

template<typename T>
inline T GameObject::RemoveComponent()
{
	for (int i = 0; i < (int)components.size(); i++)
	{
		T* component = dynamic_cast<T*>(components[i]);
		if (component != nullptr)
		{
			components.erase(i);
		}
	}
}
