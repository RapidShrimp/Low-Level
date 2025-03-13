#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "InputSystem.h"

BindableInput* InputEventHandler::CreateKeyInput(sf::Keyboard::Key DesiredKey)
{
	BindableInput* NewInput = CheckForExistingEvent(DesiredKey);
	if (NewInput != nullptr) { return NewInput;}
	
	NewInput = new BindableInput();
	NewInput->Action.KeyEvent = DesiredKey;
	KeyEvents.push_back(NewInput);
	return NewInput;
}

BindableInput* InputEventHandler::CheckForExistingEvent(sf::Keyboard::Key CheckKey)
{
	for(int i = 0; i<KeyEvents.size();i++)
	{
		if (KeyEvents[i]->Action.KeyEvent == CheckKey) 
		{
			return KeyEvents[i];
		}
	}
	return nullptr;
}

void InputEventHandler::PollInputEvents()
{
	for (int i = 0; i < KeyEvents.size(); i++)
	{
		KeyEvents[i]->PollEvent();
	}
}

void BindableInput::PollEvent()
{
	/*Contextual Inputs*/
	if (Action.IsTriggered != sf::Keyboard::isKeyPressed(Action.KeyEvent)) 
	{
		if (Action.IsTriggered) 
		{
			CallbackData.Cancelled = true;
		}
		else 
		{
			CallbackData.Started = true;
		}
	}
	Action.IsTriggered = sf::Keyboard::isKeyPressed(Action.KeyEvent);
	CallbackData.Triggering = Action.IsTriggered;
	OnInputUpdate(CallbackData);
	CallbackData.Cancelled = false;
	CallbackData.Started = false;
}
