#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/GameInstance.h"
#include "Engine/Core/Libs/GameFunctionLib.h"
#include <vector>


template<typename T>
class ObjectPooler : public GameObject {
	//TODO - Finish this class or stuff aint gonna work
public:

	ObjectPooler<T>(int PoolCount, bool StartEnabled);
	T* GetFreeObject();
	vector<GameObject*> GetAllObjects() { return m_PooledObjects; }

protected:
	void AddObjectToPooler(GameObject* InObject);
	void RemovePooledObject(GameObject* InObject);
	
	vector<GameObject*> m_PooledObjects;
};


template<typename T>
inline T* ObjectPooler<T>::GetFreeObject()
{
	//Check for a free object, return the casted type
	for (int i = 0; i < m_PooledObjects.size(); i++) 
	{
		if (!m_PooledObjects[i]->GetIsActive()) 
		{ 
			return dynamic_cast<T*>(m_PooledObjects[i]); 
		}
	}
	
	Debug::Log(this,Warning,"No Free Object Creating and Adding to the Stack");
	T* CreatedObject;
	CreatedObject = new T;
	if (CreatedObject == nullptr) { return nullptr; }
	GameInstance::GetGameInstance()->GetWorld()->SpawnObject(CreatedObject, { 0,0 }, true, "PooledObject_TypeName");

	return CreatedObject;
}

template<typename T>
inline void ObjectPooler<T>::AddObjectToPooler(GameObject* InObject)
{
	m_PooledObjects.push_back(InObject);
}

template<typename T>
inline void ObjectPooler<T>::RemovePooledObject(GameObject* InObject)
{
	//TODO - Remove Pooled Object Here?
}

template<typename T>
inline ObjectPooler<T>::ObjectPooler(int PoolCount, bool StartEnabled)
{
	//Check if class inherits from Object
	//static_assert(std::is_base_of<GameObject, T>::value, "Class is not derived from Object Class");

	//Create Objects
	T* CreatedObject;
	for (int i = 0; i < PoolCount; i++) {
		CreatedObject = new T;
		if (CreatedObject == nullptr) {
			Debug::Log(this, Error, "No Type Default Constructor, Skipping");
			return;
		}
		GameInstance::GetGameInstance()->GetWorld()->SpawnObject(CreatedObject, { 0,0 }, StartEnabled, "PooledObject" + std::to_string(i));
		AddObjectToPooler(CreatedObject);
	}


}
