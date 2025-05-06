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

class MouseInput
{
public:
	MouseInput() {};
	SinStr::Event<Math::Vector2> OnMouseInputUpdate;
	sf::Vector2f MousePos = {0,0};
	bool TriggerWhenPaused = false;
	void PollEvent();
};

class InputEventHandler
{
private:
	bool m_BlockInput = false;
	InputEventHandler() {  }; //Prevent Direct Instantiate
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


	static void BlockAllInput() { GetInstance()->m_BlockInput = true; };
	static void EnableInput() { GetInstance()->m_BlockInput = false; };

	sf::Vector2f GetMousePosition();
private:
	std::vector<BindableInput*> KeyEvents;
	std::vector<AxisInput*> AxisEvents;
	MouseInput* MouseEvents = nullptr;


public:
	BindableInput* CreateKeyInput(ActionMapping(Map),bool TriggerPaused = false);
	BindableInput* CheckForExistingEvent(sf::Keyboard::Key CheckKey);
	AxisInput* CreateAxisInput(AxisActionMapping(Map), bool TriggerPaused = false);
	MouseInput* CreateMouseInput();

	void RemoveMappings();

	void PollInputEvents();
};

