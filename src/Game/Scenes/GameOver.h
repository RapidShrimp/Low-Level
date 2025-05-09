#pragma once
#include "Engine/EngineCore.h"
#include "Game/UI/UI_GameOver.h"


class GameOver : public GameScene
{

public:
	GameOver(float Score) 
	{
		m_SceneName = "End Level";
		SetName("Game Over");

		GameObject* GameOverObj = new GameObject();
		SpawnObject(GameOverObj, Math::Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

		UI_EndGameScreen* EndScreen = new UI_EndGameScreen();
		EndScreen->SetScore(Score);
		SpawnObject(EndScreen, { 0,0 });
	};
	
	void OnLoadScene() override 
	{
		GameScene::OnLoadScene();

	};
};