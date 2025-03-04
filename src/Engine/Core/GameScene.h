#pragma once
#include "Object.h"
using namespace std;

class RendererWindow;

class GameScene {

public:
	GameScene();
	~GameScene();

protected:
	Object* SceneObjects;

private:


public:
	void RenderScene(const RendererWindow& Renderer);
};