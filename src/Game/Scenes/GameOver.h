#pragma once
#include "Engine/EngineCore.h"
#include "Game/UI/UI_GameOver.h"


class GameOver : public GameScene
{
protected:
	float m_Score;
public:
	GameOver(float Score) 
	{
		m_SceneName = "Game Over";
		SetName("Game Over");
		m_Score = Score;

	};
	
	void OnLoadScene() override 
	{
		GameScene::OnLoadScene();
		GameObject* GameOverObj = new GameObject();
		SpawnObject(GameOverObj, Math::Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

		UI_EndGameScreen* EndScreen = new UI_EndGameScreen();
		EndScreen->SetScore(m_Score);
		SpawnObject(EndScreen, { 0,0 });
	};
};