#pragma once
#include "Engine/Core/Components/Component.h"
#include "BehaviourBase.h"
#include <vector>


class SteeringManager : public Component {

public:
	
	//SteeringManager();

	void AddBehaviour(BehaviourBase* Behaviour);
	void RemoveBehaviour(BehaviourBase* Behaviour);

	//void Init(Object* Owner) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	void FixedUpdate(float deltaTime) override;
	//virtual void OnDestroy() override;*/

	Math::Vector2 GetDirection() { return m_Direction; };

protected:
	std::vector<BehaviourBase*> m_SteeringBehaviours;
	Math::Vector2 m_Direction;
	Math::Vector2 CalculateDirection();
private:

};