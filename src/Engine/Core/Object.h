#pragma once

	//Some basic functionality that all game objects should have
class Object
{
public:
	Object();
	~Object();

protected:
	Object* OwningObject =nullptr;

public:
	virtual void Init();
	virtual void OnActivate();
	virtual void OnDeactivate();
	virtual void BeginPlay();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render();
	virtual void OnDestroy();
};