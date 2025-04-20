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

	m_MinimapDraw = Special;
}

void Crystal::OnCollisionEvent(Collider* InCollider, E_CollisionEvent Event)
{
	if (InCollider->GetOwner() == nullptr) { return; }
	if (Event != TriggerEnter)  { return; }
	
	PlayerCharacter* Player = dynamic_cast<PlayerCharacter*>(InCollider->GetOwner());
	if (Player) 
	{
		Player->CollectSinibomb();
		Deactivate();
	}
	OnCrystalCollided(InCollider->GetOwner()); //Pooler will have this bound
}

void Crystal::Init(Object* OwningObject)
{
	Object::Init(OwningObject);

	RegisterComponent(m_SpriteRenderer, false, "CrystalSprite");
	RegisterComponent(m_RigidBody, false, "RigidBody");
	RegisterComponent(m_Collider, false, "Collider");

	m_Collider->OnCollisionEvent += std::bind(&Crystal::OnCollisionEvent, this, std::placeholders::_1, std::placeholders::_2);
	Debug::Log(this, Display, "Bound Event");


}

void Crystal::OnActivate()
{
	GameObject::OnActivate();
	const PlayerCharacter* Player = GameInstance::GetGameInstance()->GetPlayer();

	Math::Vector2 DesiredVector = Player->m_Transform.Location;
	 
	if (Player != nullptr) {
		
		Math::Vector2 PlayerVec = DesiredVector - m_Transform.Location ;
		PlayerVec.Normalise(PlayerVec);
		PlayerVec *= Math::Random::Range(m_CrystalSpeedRange.x, m_CrystalSpeedRange.y); //Random Speed
 		m_RigidBody->AddVelocity(PlayerVec / 200);
	}
}

void Crystal::FixedUpdate(float deltaTime)
{
	if (!isActive) { return; }
	m_Transform.Location += m_RigidBody->m_Velocity * deltaTime;
	m_Transform.Rotation += m_RigidBody->m_AngluarVelocity * deltaTime;
}
