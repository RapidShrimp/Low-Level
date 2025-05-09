#pragma once
#include <vector>
#include "functional"
#include "algorithm"

namespace SinStr {

		template<typename... T>
		struct Binding
		{
		protected:
			void* contextObj;
			std::function<void(T...)> listener;
		public:
			Binding() = default;
			Binding(std::function<void(T...)> func, void* _contextObj) 
			{
				contextObj = _contextObj;
				listener = std::move(func);
			}
			bool operator==(const Binding<T...>& rhs) { return contextObj == rhs.contextObj && listener.target_type().hash_code() == rhs.listener.target_type().hash_code(); }
			//bool operator!=(const Binding<T...>& rhs) { return !(this == rhs); }
			constexpr size_t hash_code() const noexcept { return listener.target_type().hash_code(); }
			Binding<T...>& Invoke(T... args) { listener(static_cast<T&&>(args)...); return (*this); }
			void operator()(T... args) { listener(static_cast<T&&>(args)...); }
		};

		template<typename... T>
		struct Event
		{
		private:
			std::vector<Binding<T...>> listeners;

		public:

			Event<T...>& Invoke(T... args)
			{
				for (int i = 0; i < listeners.size(); i += 1)
				{
					listeners[i].Invoke(static_cast<T&&>(args)...);
				}
				
				return (*this);
			}

			void AddListener(void* contextObj, const std::function<void(T...)> inFunc)
			{
				Binding<T...> listener = Binding<T...>(inFunc, contextObj);

				if (std::find_if(listeners.begin(), listeners.end(), [listener](Binding<T...> b) {
					return listener.hash_code() == b.hash_code() && listener == b;
					}) == listeners.end())
				{
					listeners.push_back(listener);
				}
			}
			void RemoveListener(void* contextObj, const std::function<void(T...)> inFunc)
			{
				Binding<T...> listener = Binding<T...>(inFunc, contextObj);

				std::erase_if(listeners, [listener](Binding<T...> b) {return listener.hash_code() == b.hash_code() && listener == b; });
			}
			void Empty() { listeners.clear(); }

			Event<T...>& operator()(T... args) { Invoke(args...); return (*this); }
		};

	//template<typename...T>
	//struct Binding {
	//protected:
	//	size_t hash;
	//	std::function<void(T...)> listener;
	//public:
	//	Binding(std::function<void(T...)> func) : hash(func.target_type().hash_code()), listener(std::move(func)) {}
	//	bool operator==(const Binding<T...>& rhs) { return hash == rhs.hash; }
	//	bool operator!=(const Binding<T...>& rhs) { return hash != rhs.hash; }
	//	constexpr size_t hash_code() const throw() { return hash; }
	//	Binding<T...>& Invoke(T... args) { listener(static_cast<T&&>(args)...); return(*this); }
	//	void operator()(T... args) { listener(static_cast<T&&>(args)...); }
	//};


	//template<typename... T>
	//struct Event
	//{
	//private:
	//	std::vector<Binding<T...>> listeners;

	//public:
	//	Event<T...>& Invoke(T... args)
	//	{
	//		for (Binding<T...> l : listeners) 
	//		{
	//			l.Invoke(static_cast<T&&>(args)...);
	//		} 
	//		return (*this);
	//	}

	//	void AddListener(const Binding<T...> listener)
	//	{
	//		listeners.push_back(listener);
	//		//if (std::find_if(listeners.begin(), listeners.end(), [listener](Binding<T...> b) {return listener.hash_code() == b.hash_code(); }) == listeners.end())
	//		//{
	//		//	listeners.push_back(listener);
	//		//}
	//	}

	//	void RemoveListener(const Binding<T...> listener) 
	//	{ 
	//		std::erase_if(listeners, [listener](Binding<T...> b) {
	//			return listener.hash_code() == b.hash_code(); 
	//		}); 
	//	}
	//	void Empty() { listeners.clear(); }

	//	Event<T...>& operator()(T...args) { Invoke(args...); return (*this); }
	//	Event<T...>& operator+=(const Binding<T...> listener) { AddListener(listener); return (*this); }
	//	Event<T...>& operator+=(const std::function<void(T...)> func) { Binding<T...> b(func); *this += b; return (*this); }
	//	Event<T...>& operator-=(const Binding<T...> listener) { RemoveListener(listener); return (*this); }
	//	Event<T...>& operator-=(const std::function<void(T...)> func) { Binding<T...> b(func); *this -= b; return (*this); }

	//};
}