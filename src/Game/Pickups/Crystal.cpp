#pragma once

#include "Crystal.h"
#include "Engine/Core/GameInstance.h"
#include "Game/Player/PlayerCharacter.h"
#include "Engine/Core/Libs/GameFunctionLib.h"

Crystal::Crystal()
{
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 2,2 }, {120,90});
	m_SpriteRenderer->SetSpriteScale(2, 2);
	m_RigidBody = new Rigidbody(10);
	m_Collider = new Collider(true, 5.0f);
}

void Crystal::OnCollisionEvent(Collider* InCollider, E_CollisionEvent Event)
{
	if (InCollider->GetOwner() == nullptr) { return; }
	if (Event != TriggerEnter)  { return; }
	
	PlayerCharacter* Player = dynamic_cast<PlayerCharacter*>(InCollider->GetOwner());
	if (Player) 
	{
		Player->CollectSinibomb();
	}
	OnCrystalCollided(InCollider->GetOwner()); //Pooler will have this bound
}

void Crystal::Init(Object* OwningObject)
{
	Object::Init(OwningObject);

	RegisterComponent(m_SpriteRenderer, true, "CrystalSprite");
	RegisterComponent(m_RigidBody, true, "RigidBody");
	RegisterComponent(m_Collider, true, "Collider");

	m_Collider->OnCollisionEvent += std::bind(&Crystal::OnCollisionEvent, this, std::placeholders::_1, std::placeholders::_2);
	Debug::Log(this, Display, "Bound Event");


}

void Crystal::OnActivate()
{
	return;
	 const PlayerCharacter* Player = GameInstance::GetGameInstance()->GetPlayer();

	 Math::Vector2 DesiredVector;
	 
	 if (Player != nullptr) {
		
		 Math::Vector2 PlayerVec = m_Transform.Location - Player->m_Transform.Location;
		 //TODO - Add Random Deviation Here
		 PlayerVec.Normalise(PlayerVec);
		 PlayerVec *= Math::Random::Range(m_CrystalSpeedRange.x, m_CrystalSpeedRange.y); //Random Speed
	 }
}
