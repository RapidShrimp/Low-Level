#pragma once
#include "Engine/Core/GameScene.h"

class PlayerCharacter;

class GameLevel : public GameScene 
{
protected:
	PlayerCharacter* m_Player;
public:

	GameLevel();
	void OnLoadScene() override;

	PlayerCharacter& GetPlayerCharacter() { return *m_Player; }
};