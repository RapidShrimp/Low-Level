#pragma once

struct ActionMapping 
{
public:
	ActionMapping(sf::Keyboard::Key InKey = sf::Keyboard::Key::Unknown,bool TriggerPaused = false) {
		KeyEvent = InKey;
		TriggerWhenPaused = TriggerPaused;
	}
	sf::Keyboard::Key KeyEvent;
	bool IsTriggered = false;
	bool TriggerWhenPaused = false;
};

struct AxisActionMapping 
{
public:

	AxisActionMapping(sf::Keyboard::Key Up = sf::Keyboard::Key::Up,
		sf::Keyboard::Key Down = sf::Keyboard::Key::Down,
		sf::Keyboard::Key Left = sf::Keyboard::Key::Left,
		sf::Keyboard::Key Right = sf::Keyboard::Key::Right,
		bool TriggerPaused = false)
	{
		KeyUp = Up;
		KeyDown = Down;
		KeyRight = Right;
		KeyLeft = Left;
		TriggerWhenPaused = TriggerPaused;
	}

	sf::Keyboard::Key KeyUp;
	sf::Keyboard::Key KeyDown;
	sf::Keyboard::Key KeyLeft;
	sf::Keyboard::Key KeyRight;
	bool TriggerWhenPaused = false;

};