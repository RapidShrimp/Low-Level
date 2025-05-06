#pragma once
#include "Game/main.h"
#include "Engine/Core/GameInstance.h"
#include <iostream>


class BroadcasterClass {
public:
	SinStr::Event<float> OnDoSomething;

	void BroadcastEvent() {
		OnDoSomething.Invoke(123);
	}
};

class RecieverClass {

public:

	RecieverClass(BroadcasterClass* BroadcasterPtr)
	{
		BroadcasterPtr->OnDoSomething += std::bind(&RecieverClass::TestFunc, this, std::placeholders::_1);
		cout << "bound to instance" << endl;
	}

	void TestFunc(float Num) {
		cout << std::to_string(Num) << endl;
	}
};

