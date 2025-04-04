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
	

protected:
	void AddObjectToPooler(Object* InObject);
	void RemovePooledObject(Object* InObject);
	
	vector<Object*> m_PooledObjects;
};

template<typename T>
inline T* ObjectPooler<T>::GetFreeObject()
{
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
inline void ObjectPooler<T>::AddObjectToPooler(Object* InObject)
{
	m_PooledObjects.push_back(InObject);
}

template<typename T>
inline void ObjectPooler<T>::RemovePooledObject(Object* InObject)
{
	//Remove Pooled Object Here?
}

template<typename T>
inline ObjectPooler<T>::ObjectPooler(int PoolCount, bool StartEnabled)
{
	//Check if class inherits from Object
	static_assert(std::is_base_of<Object, T>::value, "Class is not derived from Object Class");

	//Create Objects
	T* CreatedObject;
	for (int i = 0; i < PoolCount; i++) {
		CreatedObject = new T;
		if (CreatedObject == nullptr) {
			Debug::Log(this, Error, "No Type Default Constructor, Skipping");
			return;
		}
		GameInstance::GetGameInstance()->GetWorld()->SpawnObject(CreatedObject, { 0,0 }, StartEnabled, "PooledObject_TypeName" + std::to_string(i));
		AddObjectToPooler(CreatedObject);
	}


}
