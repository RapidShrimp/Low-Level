#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/GameInstance.h"
#include "InputSystem.h"

sf::Vector2i InputEventHandler::GetMousePosition()
{
	if (MouseEvents == nullptr) { return { 0,0 }; }

	return MouseEvents->MousePos;
}

BindableInput* InputEventHandler::CreateKeyInput(ActionMapping(Map))
{
	BindableInput* NewInput = CheckForExistingEvent(Map.KeyEvent);
	if (NewInput != nullptr) { return NewInput; }

	NewInput = new BindableInput(Map);
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

AxisInput* InputEventHandler::CreateAxisInput(AxisActionMapping(Map))
{
	AxisInput* NewInput = new AxisInput(Map);
	AxisEvents.push_back(NewInput);
	return NewInput;
}

MouseInput* InputEventHandler::CreateMouseInput()
{
	if (MouseEvents != nullptr)
	{
		return MouseEvents;
	}

	return MouseEvents = new MouseInput();
}

void InputEventHandler::RemoveMappings()
{
	for (int i = 0; i < KeyEvents.size(); i++)
	{
		delete KeyEvents[i];
	}
	KeyEvents.clear();
	for (int i = 0; i < AxisEvents.size(); i++)
	{
		delete AxisEvents[i];
	}
	AxisEvents.clear();
	delete MouseEvents;
	MouseEvents = nullptr;
}

void InputEventHandler::PollInputEvents()
{
	if (MouseEvents != nullptr) {
		MouseEvents->PollEvent();
	}
	for (int i = 0; i < KeyEvents.size(); i++)
	{
		KeyEvents[i]->PollEvent();
	}
	for (int i = 0; i < AxisEvents.size(); i++) 
	{
		AxisEvents[i]->PollEvent();
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

void AxisInput::PollEvent()
{
	CallbackContext Data;
	Math::Vector2 Direction = Math::Vector2({ 0,0 });
	Direction.y -= sf::Keyboard::isKeyPressed(Actions.KeyUp);
	Direction.y += sf::Keyboard::isKeyPressed(Actions.KeyDown);
	Direction.x -= sf::Keyboard::isKeyPressed(Actions.KeyLeft);
	Direction.x += sf::Keyboard::isKeyPressed(Actions.KeyRight);

	if (CurrentVector == Math::Vector2(0,0) && Direction != Math::Vector2(0, 0))
	{
		Data.Started = true;
	}
	if (CurrentVector != Math::Vector2(0, 0) && Direction == Math::Vector2(0, 0))
	{
		Data.Cancelled = true;
	}
	Data.Triggering = (Direction != Math::Vector2(0, 0));
	
	Math::Vector2::Normalise(Direction);
	CurrentVector = Direction;
	OnAxisInputUpdate(Data, CurrentVector);
}

void MouseInput::PollEvent()
{
	MousePos = sf::Mouse::getPosition(GameInstance::GetGameInstance()->GetWindow());
	OnMouseInputUpdate(Math::Vector2( MousePos.x,MousePos.y ));
}
