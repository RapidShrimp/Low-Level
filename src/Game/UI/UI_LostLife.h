#pragma once
#include "Engine/UI_Core.h"

class UI_LostLife : public UI_Base {


protected:

	Timer* m_ScreenTimer;
	UI_Text* m_LifePrompt;
	UI_Text* m_SinistarStateText;
public:
	UI_LostLife();
	virtual void Init(Object* OwningObject) override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void Render(sf::RenderWindow& Renderer) override;

private:
	void Handle_HideLostLifeMenu();
};