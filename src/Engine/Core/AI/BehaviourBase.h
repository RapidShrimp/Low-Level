#pragma once

class BehaviourBase : public Object {


public:
	BehaviourBase() {};

	virtual void Init(Object* Owner) override 
	{
		Object::Init(Owner);
		m_OwningAgent = dynamic_cast<GameObject*>(Owner);
	}
	virtual Math::Vector2 CalculateBehaviour() { return Math::Vector2::Zero();/*Override In Child*/ };
	Math::Vector2 GetNormalisedDirection() { return CalculateBehaviour().Normalised(); }
	float m_Weight = 1; //This is what the normalised direction is multiplied by

protected:
	GameObject* m_OwningAgent = nullptr; //The Owner to the Steering Manager
	Math::Vector2 m_ForceDirection; //Resulting calculation Direction - This value should only be used for debug purposes
};





class Seek : public BehaviourBase {

public:
	Seek(GameObject* Target) 
	{
		m_SeekTarget = Target;
	};
	

	void SetTarget(GameObject* Target) { m_SeekTarget = Target; }
	virtual Math::Vector2 CalculateBehaviour() override 
	{
		if (m_OwningAgent ==nullptr || m_SeekTarget == nullptr) {

			return Math::Vector2::Zero();
		}

		m_ForceDirection =  m_SeekTarget->m_Transform.Location - m_OwningAgent->m_Transform.Location;
		return m_ForceDirection.Normalised() * m_Weight;
	}

protected:
	GameObject* m_SeekTarget;
};




class Flee : public BehaviourBase {
public:
	Flee(GameObject* Target)
	{
		m_FleeTarget = Target;
	};
	void SetTarget(GameObject* Target) { m_FleeTarget = Target; }

	virtual Math::Vector2 CalculateBehaviour() override
	{
		if (m_OwningAgent == nullptr || m_FleeTarget == nullptr) {

			return Math::Vector2::Zero();
		}

		m_ForceDirection = m_OwningAgent->m_Transform.Location - m_FleeTarget->m_Transform.Location;
		return m_ForceDirection.Normalised() * m_Weight;
	}

protected:
	GameObject* m_FleeTarget = nullptr;
};





class Seperation : public BehaviourBase {

};
