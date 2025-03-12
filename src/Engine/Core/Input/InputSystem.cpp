#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "InputSystem.h"


#pragma region Bindable Inputs

template<typename U>
BindableInput::BindableInput(sf::Keyboard::Key RegisteredKey, U ...)
{
	//CallbackContext<U> CallbackType = CallbackContext<U>();
	OnInputUpdate = new SinStr::Event<CallbackContext>();
}

BindableInput::BindableInput(sf::Keyboard::Key RegisteredKey)
{
	OnInputUpdate = new SinStr::Event<CallbackContext>();

}

void BindableInput::CalculateInput()
{
	//InputContext Context;
	//if (IsHeld && sf::Keyboard::isKeyPressed(ListenerKey)) 
	//{
	//	Context = triggering;
	//}
	//else 
	//{
	//	Context = IsHeld ? cancelled : started;
	//}
	//OnInputUpdate.Invoke(Context);
	//IsHeld = sf::Keyboard::isKeyPressed(ListenerKey);
}
#pragma endregion

#pragma region Input Event Handler


template<typename U>
BindableInput* InputEventHandler::CreateInput(sf::Keyboard::Key RegisteredKey, U ReturnType)
{
	BindableInput* NewInput = new BindableInput(RegisteredKey, ReturnType);
	if (NewInput != nullptr) 
	{
		RegisteredInputs.push_back(NewInput);
	}
	return NewInput;
}

BindableInput* InputEventHandler::CreateInput(sf::Keyboard::Key RegisteredKey)
{

	return nullptr;
}

void InputEventHandler::Update()
{
	Debug::Log(this,Display ,"Input System Update");
}
#pragma endregion