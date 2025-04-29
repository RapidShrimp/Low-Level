#pragma once

namespace SinStr {

	class Timer {

	public:
		SinStr::Event<> OnUpdate;
		SinStr::Event<> OnFixedUpdate;

	private:
		unsigned long m_PhysicsTimeStep

	};


}