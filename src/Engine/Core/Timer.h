#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/GameInstance.h"

class Timer {

public:
	SinStr::Event<> OnTimerUpdated;
	SinStr::Event<> OnTimerCompleted;

protected:
	bool isActive;
	bool m_TickPaused;
	bool m_Looping;
	float m_MaxTime;
	float m_CurrentTime;
	float m_Deviation;
public:

	//Starts and binds to the game instance loop
	//(Excludes Pause Functionality)
	//Duration in Seconds

	//Independant Timer, Self Managing, Fires only once and then deletes itself
	Timer(float Duration, float RandomDeviation) 
	{
		isActive = true;
		m_TickPaused = false;
		m_Looping = false;
		m_MaxTime = Duration * 500;
		m_CurrentTime = 0;
		m_Deviation = RandomDeviation;
		GameInstance::GetGameInstance()->OnFixedUpdate += std::bind(&Timer::Handle_IndependantOnFixedUpdate, this, std::placeholders::_1);

	}

	//Unmanaged Timer
	Timer(float Duration, bool Looping ,float RandomDeviation = 0.0f,bool TickPaused = false)
	{
		m_TickPaused = TickPaused;
		m_Looping = Looping;
		m_MaxTime = Duration * 500.0f; 
		m_CurrentTime = 0;
		m_Deviation = RandomDeviation;
		isActive = false;
		Debug::Log(nullptr, Display, "Timer-Created");

	}
	void PauseTimer() { isActive = false; }
	void ResumeTimer() { isActive = true; }
	void StartTimer() 
	{ 
		GameInstance::GetGameInstance()->OnFixedUpdate += std::bind(&Timer::Handle_OnFixedUpdate, this, std::placeholders::_1);
		isActive = true; 
	}

	//This will set the timer current step to 0
	//*Note* If a timer is running it will not stop
	void ResetTimer() { m_CurrentTime = 0; }


	void DestroyIndependantTimer() {
		PauseTimer();
		GameInstance::GetGameInstance()->OnFixedUpdate -= std::bind(&Timer::Handle_IndependantOnFixedUpdate, this, std::placeholders::_1);
		OnTimerUpdated.Empty();
		OnTimerCompleted.Empty();
		Debug::Log(nullptr, Display, "Independant Timer Destroyed");

		delete this;
	};
	//This will clear all bindings and destroy the timer
	//If not removed by the creator of the timer a memory leak occurs
	void DestroyTimer()
	{
		PauseTimer();
		GameInstance::GetGameInstance()->OnFixedUpdate -= std::bind(&Timer::Handle_OnFixedUpdate, this, std::placeholders::_1);
		OnTimerUpdated.Empty();
		OnTimerCompleted.Empty();
		Debug::Log(nullptr, Display, "Timer Destroyed");

		delete this;
	};

private:
	void Handle_OnFixedUpdate(float TimeStep)
	{
		if (GameInstance::GetGameInstance()->GetWorld()->IsGamePaused() && !m_TickPaused) { return; } //Dont Tick timer if paused
		if (!isActive) { return; }

		OnTimerUpdated.Invoke();
		m_CurrentTime += TimeStep;
		if (m_CurrentTime < m_MaxTime) { return; }

 		OnTimerCompleted.Invoke();
		Debug::Log(nullptr, Display, "Timer-Complete");

		if (m_Looping)
		{
			Debug::Log(nullptr, DebugNone, "Timer-Looped");
			ResetTimer();
			m_CurrentTime += Math::Random::Range(-m_Deviation, m_Deviation);
		}
		else
		{
			m_CurrentTime = 0;
			PauseTimer();
		}
	}

	void Handle_IndependantOnFixedUpdate(float TimeStep)
	{
		if (GameInstance::GetGameInstance()->GetWorld()->IsGamePaused() && !m_TickPaused) { return; } //Dont Tick timer if paused
		if (!isActive) { return; }

		OnTimerUpdated.Invoke();
		m_CurrentTime += TimeStep;
		if (m_CurrentTime < m_MaxTime) { return; }

		OnTimerCompleted.Invoke();
		DestroyIndependantTimer();

	}
};

