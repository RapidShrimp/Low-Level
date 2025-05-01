#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "SteeringManager.h"
#include "Engine/Core/Object.h"
#include "Engine/Core/GameInstance.h"

void SteeringManager::AddBehaviour(BehaviourBase* Behaviour)
{

	if (Behaviour == nullptr) {
		Debug::Log(this, Error, "Cannot Add NULL behaviour");
		return;
	}

	if (GetOwner() == nullptr) 
	{ 
		Debug::Log(this, Error, "Cannot Add behaviour, No Owner");
		return; 
	}
	Behaviour->Init(GetOwner());
	m_SteeringBehaviours.push_back(Behaviour);
}

void SteeringManager::RemoveBehaviour(BehaviourBase* Behaviour)
{
	//Remove Here
}

void SteeringManager::Render(sf::RenderWindow& Renderer)
{
	if (GameInstance::GetGameInstance()->ShouldDrawDebug()) 
	{
		return;

		//Assertion Error Here
		sf::ConvexShape Line;
		Line.setPoint(0, GetOwner()->m_Transform.Location.ToSF());
		Line.setPoint(1, (GetOwner()->m_Transform.Location + m_Direction).ToSF());

		Renderer.draw(Line);

		//sf::Vertex Lines[2];
		//Lines[0].position = GetOwner()->m_Transform.Location.ToSF();
		//Lines[0].color = sf::Color::Magenta;

		//Lines[1].position = (GetOwner()->m_Transform.Location + m_Direction).ToSF();
		//Lines[0].color = sf::Color::Magenta;

		//Renderer.draw(Lines)
	}
}

void SteeringManager::FixedUpdate(float deltaTime)
{
	m_Direction = CalculateDirection();
}

Math::Vector2 SteeringManager::CalculateDirection()
{
	if (m_SteeringBehaviours.size() == 0) { return Math::Vector2().Zero(); }

	Math::Vector2 DesiredDirection = Math::Vector2::Zero();

	for (int Behaviour = 0; Behaviour < m_SteeringBehaviours.size(); Behaviour++) 
	{
		if (m_SteeringBehaviours[Behaviour] == nullptr) 
		{
			//Remove nullptr Behaviour
			continue;
		}

		DesiredDirection += m_SteeringBehaviours[Behaviour]->CalculateBehaviour();

	}

	return DesiredDirection;
}
