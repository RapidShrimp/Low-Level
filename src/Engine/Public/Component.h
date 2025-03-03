#include "Transform.h"



class Component 
{
	GameObject* Owner = nullptr;

	void RegisterComponent(GameObject* Parent);
	void DestroyComponent();
	void Init();

	void On
};