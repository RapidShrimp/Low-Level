#pragma once
#include "ActionMapping.h"
#include "./Engine/Core/Events/Event.h"
struct CallbackContext 
{
	bool Started = 0;
	bool Triggering = 0;
	bool Cancelled = 0;

};

class BindableInput
{
public:
	BindableInput(ActionMapping(Map)) { Action = Map; }
	ActionMapping Action;
	CallbackContext CallbackData;
	SinStr::Event<CallbackContext> OnInputUpdate;
	void PollEvent();
};

class AxisInput 
{
public:
	AxisInput(AxisActionMapping(Map)) { Actions = Map; }
	AxisActionMapping Actions;
	SinStr::Event<CallbackContext,Math::Vector2> OnAxisInputUpdate;
	Math::Vector2 CurrentVector = Math::Vector2(0,0);
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
	std::vector<AxisInput*> AxisEvents;

public:
	BindableInput* CreateKeyInput(ActionMapping(Map));
	BindableInput* CheckForExistingEvent(sf::Keyboard::Key CheckKey);
	AxisInput* CreateAxisInput(AxisActionMapping(Map));

	void PollInputEvents();
};

