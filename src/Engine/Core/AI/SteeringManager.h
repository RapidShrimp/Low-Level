#pragma once
#include "Engine/Core/Components/Component.h"
#include "BehaviourBase.h"
#include <vector>


class SteeringManager : public Component {

public:
	
	//SteeringManager();

	void AddBehaviour(BehaviourBase* Behaviour, float Weight = 1, bool isActive = true);
	void RemoveBehaviour(BehaviourBase* Behaviour);

	//void Init(Object* Owner) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	void FixedUpdate(float deltaTime) override;
	virtual void OnDestroy() override;

	Math::Vector2 GetDirection() { return m_Direction; };

	template<typename U>
	void SetBehaviourActive(bool IsActive);

	template<typename U> 
	U* GetBehaviour();
protected:
	std::vector<BehaviourBase*> m_SteeringBehaviours;
	Math::Vector2 m_Direction;
	Math::Vector2 CalculateDirection();
private:

};

template<typename U>
inline void SteeringManager::SetBehaviourActive(bool IsActive)
{

	static_assert(std::is_base_of<BehaviourBase, U>::value, "Class is not derived from Steering behaviour Class");
	return;

	BehaviourBase* Behaviour = GetBehaviour<U>();
	if (Behaviour == nullptr) 
	{ 
		Debug::Log(this, Warning, "No Behaviour Attached");
		return; 
	}

	if (IsActive) {
		Behaviour->Activate();
	}
	else {
		Behaviour->Deactivate();
	}
}

template<typename U>
inline U* SteeringManager::GetBehaviour()
{
	for (int Behaviour = 0; Behaviour < m_SteeringBehaviours.size(); Behaviour++)
	{
		U* FoundObject = dynamic_cast<U*>(m_SteeringBehaviours[Behaviour]);
		if (FoundObject != nullptr) { return FoundObject; }
	}
	return nullptr;
}