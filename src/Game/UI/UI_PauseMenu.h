#pragma once
#include "Engine/UI_Core.h"

class UI_PauseMenu : public UI_Base {


protected:

	Timer* m_BlinkTimer;
	UI_Text* m_PausePrompt;
	UI_Text* m_PauseText;
public:
	UI_PauseMenu();
	virtual void Init(Object* OwningObject) override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
protected:
	void ShowPauseMenu();
	void HidePauseMenu();


private:
	void Handle_BlinkTimerTrigger();

};