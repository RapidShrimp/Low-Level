#pragma once

#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/Components/Rigidbody.h"

class BehaviourBase : public Object {


public:
	BehaviourBase() {};

	virtual void Init(GameObject* Owner)
	{
		m_OwningAgent = static_cast<GameObject*>(Owner);
		Object::Init(Owner);
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
	
	Seek(GameObject* Target = nullptr) 
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

	Flee(float Radius = 50, GameObject* Target = nullptr) 
	{
		m_FleeRadius = Radius;
		m_FleeTarget = Target;		
	}

	float m_FleeRadius = 50;
	void SetTarget(GameObject* Target) { m_FleeTarget = Target; }

	virtual Math::Vector2 CalculateBehaviour() override
	{
		if (m_OwningAgent == nullptr || m_FleeTarget == nullptr) {

			return Math::Vector2::Zero();
		}


		Math::Vector2 Distance = m_OwningAgent->m_Transform.Location - m_FleeTarget->m_Transform.Location;

		if (Distance.Length() <= m_FleeRadius) 
		{
			//Get Distance Based Flee Strength
			m_ForceDirection = Distance * std::lerp(m_Weight, 0, std::min(Distance.Length(), m_FleeRadius) / m_FleeRadius);
			return m_ForceDirection;
		}
		else 
		{
			return Math::Vector2::Zero();
		}
		
	}

protected:
	GameObject* m_FleeTarget = nullptr;
};


class Pursuit : public Seek
{
public:
	Pursuit(GameObject* Target) {
		m_SeekTarget = Target;
	}

	virtual Math::Vector2 CalculateBehaviour() override
	{
		if (m_OwningAgent == nullptr || m_SeekTarget == nullptr) {

			return Math::Vector2::Zero();
		}

		

		Rigidbody* OwnerVel = m_SeekTarget->FindComponentOfType<Rigidbody>();
		Rigidbody* TargetVel = m_SeekTarget->FindComponentOfType<Rigidbody>();
		if (OwnerVel == nullptr || TargetVel == nullptr) 
		{
			Debug::Log(this, Error, "No Rigid Body on either Target or Owner");
			return Math::Vector2::Zero(); 
		}
		
		m_ForceDirection = m_SeekTarget->m_Transform.Location - m_OwningAgent->m_Transform.Location;
		float CombinedSpeed = OwnerVel->m_Velocity.Length() + TargetVel->m_Velocity.Length();
		float Prediction = m_ForceDirection.Length() / CombinedSpeed;

		Math::Vector2 SeekTarget = m_SeekTarget->m_Transform.Location + m_OwningAgent->m_Transform.Location * Prediction;
		m_ForceDirection = SeekTarget - m_OwningAgent->m_Transform.Location;

		return m_ForceDirection.Normalised() * m_Weight;
	}

protected:
};


class Separation : public BehaviourBase {

public:

	Separation(float SeparateDistance = 50, std::vector<GameObject*> Targets = {})
	{
		m_SeparateDistance = SeparateDistance;
		m_Targets = Targets;
	}

	std::vector<GameObject*> m_Targets;
	float m_SeparateDistance = 50;

	void AddTarget(GameObject* Target) { m_Targets.push_back(Target); }
	void RemoveTarget(GameObject* Target) {/*Remove Targets Here*/ }
	void SetTargets(std::vector<GameObject*> Targets) 
	{ 

		m_Targets = Targets; 

		//Remove Self if added to the vector
		auto Entity = std::find(m_Targets.begin(), m_Targets.end(), m_OwningAgent);
		if (Entity != m_Targets.end())
		{
			m_Targets.erase(Entity);
		}
	}

	
	virtual Math::Vector2 CalculateBehaviour() override
 	{
		if (m_Targets.size() == 0) { return Math::Vector2::Zero(); }

		if (m_OwningAgent == nullptr) {
			return Math::Vector2::Zero();
		}

		Math::Vector2 SeparateVector = Math::Vector2::Zero();
		int Avoiding = 0;

		for (GameObject* Entity : m_Targets) {

			if (Entity == nullptr) {
				Debug::Log(this, Error, "Entity in seperation behaviour is nullptr");
				continue;
			}

			Math::Vector2 Distance = m_OwningAgent->m_Transform.Location - Entity->m_Transform.Location;

			if (Distance.Length() > m_SeparateDistance)
			{
				continue;
			}
	
			//Separate strength based on distance
			SeparateVector += Distance.Normalised() * (1.0f/Distance.Length());
			Avoiding++;
		}

		m_ForceDirection = SeparateVector * m_Weight;
		return m_ForceDirection;

	}

};
