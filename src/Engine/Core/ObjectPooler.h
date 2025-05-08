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
	vector<T*> GetAllObjects() { return m_PooledObjects; }
	
	template<typename U>
	vector<U*> GetObjectsAs();

protected:
	void AddObjectToPooler(T* InObject);
	void RemovePooledObject(T* InObject);
	
	vector<T*> m_PooledObjects;
};


template<typename T>
inline T* ObjectPooler<T>::GetFreeObject()
{
	//Check for a free object, return the casted type
	for (int i = 0; i < m_PooledObjects.size(); i++) 
	{
		if (m_PooledObjects[i] == nullptr) { continue; }
		if (!m_PooledObjects[i]->GetIsActive()) 
		{ 
			return dynamic_cast<T*>(m_PooledObjects[i]); 
		}
	}
	
	T* CreatedObject;
	CreatedObject = new T;
	std::string ClassName = typeid(T).name();
	Debug::Log(this,Warning,"No Free Object Creating and Adding " + ClassName + " to the Stack");
  	if (CreatedObject == nullptr) { return nullptr; }
	GameInstance::GetGameInstance()->GetWorld()->SpawnObject(CreatedObject, { 0,0 }, true, "PO_" + ClassName);

	return CreatedObject;
}

template<typename T>
inline void ObjectPooler<T>::AddObjectToPooler(T* InObject)
{
	m_PooledObjects.push_back(InObject);
}

template<typename T>
inline void ObjectPooler<T>::RemovePooledObject(T* InObject)
{
	//TODO - Remove Pooled Object Here?
}

template<typename T>
inline ObjectPooler<T>::ObjectPooler(int PoolCount, bool StartEnabled)
{
	//Check if class inherits from Object
	static_assert(std::is_base_of<GameObject, T>::value, "Class is not derived from Object Class");

	//Create Objects
	T* CreatedObject;
	for (int i = 0; i < PoolCount; i++) {
		CreatedObject = new T;
		if (CreatedObject == nullptr) {
			Debug::Log(this, Error, "No Type Default Constructor, Skipping");
			return;
		}

		std::string ClassName = typeid(T).name();
		GameInstance::GetGameInstance()->GetWorld()->SpawnObject(CreatedObject, { 0,0 }, StartEnabled, "PO_" +ClassName +"_" + std::to_string(i));
		AddObjectToPooler(CreatedObject);
	}
	GameInstance::GetGameInstance()->GetWorld()->SpawnObject(this, { 0,0 }, true, "Object Pooler");


}

template<typename T>
template<typename U>
inline vector<U*> ObjectPooler<T>::GetObjectsAs()
{
	std::vector<U*> TypePool;
	for (T* Object : m_PooledObjects) 
	{
		U* CastedObject = dynamic_cast<U*>(Object);
		if (CastedObject == nullptr) { continue; }
		TypePool.push_back(CastedObject);
	}

	return TypePool;
}
