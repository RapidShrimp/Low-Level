#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"

class Timer {

public:
	SinStr::Event<> OnTimerUpdated;
	SinStr::Event<> OnTimerCompleted;

protected:
	bool isActive;
	bool m_Looping;
	float m_MaxTime;
	float m_CurrentTime;

public:

	//Starts and binds to the game instance loop
	//(Excludes Pause Functionality)
	//Duration in Seconds
	Timer(float Duration, bool Looping)
	{
		//GameInstance::GetGameInstance()->OnFixedUpdate += std::bind(&Timer::Handle_OnFixedUpdate, this, std::placeholders::_1);
		m_Looping = Looping;
		m_MaxTime = Duration * 500.0f;

		Debug::Log(nullptr, Confirm, "Timer-Started");

	}

	void PauseTimer() { isActive = false; }
	void ResumeTimer() { isActive = true; }

	//This will set the timer current step to 0
	//*Note* If a timer is running it will not stop
	void ResetTimer() { m_CurrentTime = 0; }

	//This will clear all bindings and destroy the timer
	//If not removed by the creator of the timer a memory leak occurs
	void DestroyTimer()
	{
		PauseTimer();
		//GameInstance::GetGameInstance()->OnFixedUpdate -= std::bind(&Timer::Handle_OnFixedUpdate, this, std::placeholders::_1);
		OnTimerUpdated.Empty();
	};

private:
	void Handle_OnFixedUpdate(float TimeStep)
	{
		//OnTimerUpdated();
		m_CurrentTime += TimeStep;
		if (m_CurrentTime < m_MaxTime) { return; }

		OnTimerCompleted.Invoke();
		Debug::Log(nullptr, Confirm, "Timer-Complete");

		if (m_Looping)
		{
			Debug::Log(nullptr, Confirm, "Timer-Looped");
			ResetTimer();
		}
		else
		{
			m_CurrentTime = 0;
			PauseTimer();
		}

	}
};

