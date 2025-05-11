#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/GameInstance.h"

class Timer : public Object {

public:
	SinStr::Event<> OnTimerUpdated;
	SinStr::Event<> OnTimerCompleted;
	SinStr::Event<Timer*> OnRemoveTimer;

protected:
	bool isActive;
	bool m_TickPaused;
	bool m_Looping;
	float m_MaxTime;
	float m_CurrentTime;
	float m_Deviation;
	bool m_SingleUse;
public:
	
	//For single firing functionality;
	//Automatically Adds itself to the World
	Timer(float Duration) 
	{
		m_MaxTime = Duration * 500;
		m_TickPaused = false;
		m_Looping = false;
		m_MaxTime = Duration * 500.0f;
		m_CurrentTime = 0;
		m_Deviation = 0;
		isActive = false;
		GameInstance::GetWorld()->AddSingleUseTimer(this);
		StartTimer();
	}

	//Self Managed Timer - For calling multiple times
	Timer(float Duration, bool Looping, bool AutoStart = true, float RandomDeviation = 0.0f, bool TickPaused = false)
	{
		m_TickPaused = TickPaused;
		m_Looping = Looping;
		m_MaxTime = Duration * 500.0f;
		m_CurrentTime = 0;
		m_Deviation = RandomDeviation;
		isActive = false;
		m_SingleUse = false;
		Debug::Log(nullptr, Display, "Timer-Created");

		if (AutoStart) {
			m_CurrentTime = GetRandomDeviation();
			StartTimer();
		}
	}

	virtual void FixedUpdate(float TimeStep) override
	{
		if (GameInstance::GetGameInstance()->GetWorld()->IsGamePaused() && !m_TickPaused) { return; } //Dont Tick timer if paused
		if (!isActive) { return; }

		OnTimerUpdated.Invoke();
		m_CurrentTime += TimeStep;
		if (m_CurrentTime < m_MaxTime) { return; }

		OnTimerCompleted.Invoke();
		Debug::Log(nullptr, DebugNone, "Timer Completed");

		if (m_Looping)
		{
			Debug::Log(nullptr, DebugNone, "Timer Looped");
			ResetTimer();
		}
		else if(m_SingleUse)
		{
			DestroyTimer();
		}
		else 
		{
			PauseTimer();
			ResetTimer();
		}
	};

	//This will set the timer current step to 0
	//*Note* If a timer is running it will not stop
	void ResetTimer() { m_CurrentTime = 0; }
	void PauseTimer() { isActive = false; }
	void ResumeTimer() { isActive = true; }
	void StartTimer() 
	{
		m_CurrentTime = 0;
		isActive = true; 
	}
	float GetRandomDeviation() {
		return Math::Random::Range(-m_Deviation, m_Deviation);
	}
	//This will clear all bindings and pause any functionality
	void DestroyTimer()
	{
		PauseTimer();
		OnTimerUpdated.Empty();
		OnTimerCompleted.Empty();
		OnRemoveTimer.Invoke(this);
		OnRemoveTimer.Empty();
	};

};

