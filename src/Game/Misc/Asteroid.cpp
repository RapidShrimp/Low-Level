#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/GameInstance.h"
#include "Asteroid.h"

Asteroid::Asteroid()
{
	m_Health = new HealthComponent();
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 152,32 }, {1,144},5,1);
	m_Collider = new Collider(false, { 48,48 });
	m_RigidBody = new Rigidbody(0.4f);
}

Asteroid::~Asteroid()
{

}

void Asteroid::Init(Object* OwningObject)
{
	RegisterComponent(m_Health, true, "Heatlh");
	RegisterComponent(m_SpriteRenderer, true, "Sprite Renderer");
	RegisterComponent(m_Collider, true, "Circle Collider");
	RegisterComponent(m_RigidBody, true, "Rigid Body");

	m_Health->OnDamageTaken += std::bind(&Asteroid::Handle_OnAsteroidHit, this, std::placeholders::_1);
	m_Health->OnDeath += std::bind(&Asteroid::Handle_OnAsteroidDestroyed, this,0);

}

void Asteroid::OnActivate()
{
	if (m_SpriteRenderer == nullptr) { return; }
	float size = Math::Random::Range(1.0f, 1.0f);
	m_Transform.Scale = { size,size };
	m_SpriteRenderer->SetSprite((int)Math::Random::Range(0.0f, 4.0f),0);
}

void Asteroid::BeginPlay()
{
}

void Asteroid::Update()
{
}

void Asteroid::FixedUpdate(float DeltaTime)
{
}

void Asteroid::Handle_OnAsteroidHit(float InDamage)
{
	Debug::Log(this, DebugNone, "Hit");
	Hits++;
	if (Hits == CrystalRequireHits) {
		Hits = 0;
		OnSpawnCrystal(m_Transform.Location);
	}
}

void Asteroid::Handle_OnAsteroidDestroyed(float InDamage)
{
	Debug::Log(this, Display, "Asteroid Destroyed");
	OnSpawnCrystal(m_Transform.Location);
	OnAsteroidDestroyed();
	Deactivate();
}
