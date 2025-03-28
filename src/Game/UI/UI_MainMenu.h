#pragma once
#include "Engine/Core/UI/UI_Base.h"


class UI_MainMenu : public UI_Base {

public:

	virtual void Init(Object* OwningObject) override;

	SinStr::Event<int> OnNavigationPressed;

	void Handle_UpInput(CallbackContext Context);
	void Handle_DownInput(CallbackContext Context);
	void Handle_Select(CallbackContext Context);

	
};