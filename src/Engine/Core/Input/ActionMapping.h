#pragma once

class ActionMapping 
{
public:
	ActionMapping(sf::Keyboard::Key InKey = sf::Keyboard::Key::Unknown) {
		KeyEvent = InKey;
	}
	sf::Keyboard::Key KeyEvent;
	bool IsTriggered = false;
};

class AxisActionMapping 
{
public:

	AxisActionMapping(sf::Keyboard::Key Up = sf::Keyboard::Key::Up,
		sf::Keyboard::Key Down = sf::Keyboard::Key::Down,
		sf::Keyboard::Key Left = sf::Keyboard::Key::Left,
		sf::Keyboard::Key Right = sf::Keyboard::Key::Right)
	{
		KeyUp = Up;
		KeyDown = Down;
		KeyRight = Right;
		KeyLeft = Left;
	}

	sf::Keyboard::Key KeyUp;
	sf::Keyboard::Key KeyDown;
	sf::Keyboard::Key KeyLeft;
	sf::Keyboard::Key KeyRight;

};