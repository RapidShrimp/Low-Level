#pragma once
#include "Object.h"
#include "SFML/Graphics.hpp"
#include "GameScene.h"

using namespace std;
using namespace sf;

class GameInstance : Object {

	shared_ptr<GameScene> CurrentScene;
	shared_ptr<GameScene> NextScene;

	void Init() override;
	void Update() override;
	void Render() override;
	RenderWindow GameWindow;

};