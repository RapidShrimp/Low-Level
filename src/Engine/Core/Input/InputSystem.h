#pragma once
#include "ActionMapping.h"
#include "./Engine/Core/Events/Event.h"
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

	InputEventHandler() {}; //Prevent Direct Instantiate
	InputEventHandler(const InputEventHandler&) = delete; //Prevent Copy Constructor
	InputEventHandler& operator=(const InputEventHandler&) = delete; //Prevent Copy Assign
	static InputEventHandler* m_InputSystemInstance;
	~InputEventHandler();

public:
	static inline InputEventHandler* GetInstance() /*Create / Get;*/
	{
		if (m_InputSystemInstance == nullptr) { m_InputSystemInstance = new InputEventHandler(); }
		return m_InputSystemInstance;
	};

private:
	std::vector<BindableInput*> KeyEvents;
public:
	BindableInput* CreateKeyInput(sf::Keyboard::Key DesiredKey);
	BindableInput* CheckForExistingEvent(sf::Keyboard::Key CheckKey);
	void PollInputEvents();
};

