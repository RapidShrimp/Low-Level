#pragma once
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Libs/Maths.h"
#include "Engine/Core/Components/Component.h"

struct CallbackContext
{
	enum Result {
		Started,
		Triggering,
		Cancelled
	};
};

class BindableInput
{
public:
	template<typename U>
	BindableInput(sf::Keyboard::Key RegisteredKey, U...);
	BindableInput(sf::Keyboard::Key RegisteredKey);

	SinStr::Event<CallbackContext>* OnInputUpdate;
	virtual void CalculateInput();
private:
	bool IsHeld = false;
	sf::Keyboard::Key ListenerKey = sf::Keyboard::Key::Unknown;
};

class InputEventHandler : public GameObject
{
private:
	std::vector<BindableInput*> RegisteredInputs;
public:
	template<typename U>
	BindableInput* CreateInput(sf::Keyboard::Key RegisteredKey,U ReturnTypes);
	BindableInput* CreateInput(sf::Keyboard::Key RegisteredKey);

	virtual void Update() override;
};

struct XYAxisKey
{
	sf::Keyboard::Key Up = sf::Keyboard::Key::W;
	sf::Keyboard::Key Down = sf::Keyboard::Key::S;
	sf::Keyboard::Key Left = sf::Keyboard::Key::A;
	sf::Keyboard::Key Right = sf::Keyboard::Key::D;

	Math::Vector2 GetXYVector()
	{
		Math::Vector2 Direction = Math::Vector2(0, 0);
		Direction.y += sf::Keyboard::isKeyPressed(Up);
		Direction.y -= sf::Keyboard::isKeyPressed(Down);
		Direction.x += sf::Keyboard::isKeyPressed(Right);
		Direction.y -= sf::Keyboard::isKeyPressed(Left);
		return Direction;
	}
};