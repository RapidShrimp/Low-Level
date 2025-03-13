#pragma once
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Input/ActionMapping.h"

enum CallbackContext 
{
	Started,
	Triggering,
	Cancelled
};

class BindableInput
{
public:
	SinStr::Event<CallbackContext> OnInputUpdate;
	ActionMapping Action;
	void PollEvent();
};

class InputEventHandler
{
private:
	std::vector<BindableInput*> KeyEvents;
public:
	BindableInput* CreateKeyInput(sf::Keyboard::Key DesiredKey);
	BindableInput* CheckForExistingEvent(sf::Keyboard::Key CheckKey);
	void PollInputEvents();
};

