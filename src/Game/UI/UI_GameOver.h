#pragma once
#include "Engine/UI_Core.h"

class UI_EndGameScreen : public UI_Base 
{
public:
	virtual void Init(Object* OwningObject) override;
	void SetScore(float Score);
	void Handle_Select(CallbackContext Context);
};