#pragma once
#include "Asteroid.h"

Asteroid::Asteroid()
{
	m_Health = new HealthComponent();
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 152,32 }, {1,144},5,1);
	m_Collider = new Collider(false, { 32,32 });
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
