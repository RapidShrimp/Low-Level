#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/GameInstance.h"
#include "InputSystem.h"

sf::Vector2f InputEventHandler::GetMousePosition()
{
	if (MouseEvents == nullptr) { return { 0,0 }; }

	return MouseEvents->MousePos;
}

BindableInput* InputEventHandler::CreateKeyInput(ActionMapping(Map), bool TriggerPaused)
{
	BindableInput* NewInput = CheckForExistingEvent(Map.KeyEvent);
	if (NewInput != nullptr) { return NewInput; }
	Map.TriggerWhenPaused = TriggerPaused;
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

AxisInput* InputEventHandler::CreateAxisInput(AxisActionMapping(Map), bool TriggerPaused)
{
	Map.TriggerWhenPaused = TriggerPaused;
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

	if (m_BlockInput) { return; }
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
	if (GameInstance::GetGameInstance()->GetWorld()->IsGamePaused() && !Action.TriggerWhenPaused) { return; }
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
	OnInputUpdate.Invoke(CallbackData);
	CallbackData.Cancelled = false;
	CallbackData.Started = false;
}

void AxisInput::PollEvent()
{
	if (GameInstance::GetGameInstance()->GetWorld()->IsGamePaused() && !Actions.TriggerWhenPaused) { return; }

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
	OnAxisInputUpdate.Invoke(Data, CurrentVector);
}

void MouseInput::PollEvent()
{
	sf::Vector2i WorldMousePos = sf::Mouse::getPosition(GameInstance::GetGameInstance()->GetWindow());
	sf::Vector2f CamLocation = GameInstance::GetGameInstance()->GetCamera().getCenter();
	CamLocation = { CamLocation.x - WINDOW_WIDTH / 2, CamLocation.y - WINDOW_HEIGHT / 2 };
	MousePos = sf::Vector2f({ (float)WorldMousePos.x,(float)WorldMousePos.y }) + CamLocation;
	//MousePos = GameInstance::GetGameInstance()->GetCamera().getCenter( ;// .mapCoordsToPixel({ static_cast<float>(MousePos.x), static_cast<float>(MousePos.y) });
	OnMouseInputUpdate(Math::Vector2( MousePos.x,MousePos.y ));
}
