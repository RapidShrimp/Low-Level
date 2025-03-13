#pragma once
#include <iostream>
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "InputSystem.h"

BindableInput* InputEventHandler::CreateKeyInput(sf::Keyboard::Key DesiredKey)
{
	BindableInput* NewInput = CheckForExistingEvent(DesiredKey);
	if (NewInput != nullptr)
	{
		KeyEvents.push_back(NewInput);
	}
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
	CallbackContext CallbackType;
	if (Action.IsTriggered == sf::Keyboard::isKeyPressed(Action.KeyEvent))
	{
		CallbackType = Triggering;
	}
	else 
	{
		CallbackType = Action.IsTriggered ? Cancelled : Started;
	}
	OnInputUpdate(CallbackType);
}
