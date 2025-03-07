#pragma once
#include "PlayerCharacter.h"
#include <iostream>

PlayerCharacter::PlayerCharacter()
{
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Init(Object* OwningObject)
{
	Object::Init(OwningObject);
}

void PlayerCharacter::BeginPlay()
{
	cout << "Player Spawned" << endl;
}