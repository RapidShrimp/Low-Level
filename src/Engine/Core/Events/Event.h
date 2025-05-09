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
			
			//TO- Look at this
			Binding<T...>& Invoke(T... args) {
				 listener(static_cast<T&&>(args)...);  return (*this); }	// EDIT - Added conditional to avoid empty listener 
			void operator()(T... args) { listener(static_cast<T&&>(args)...); }
		};

		template<typename... T>
		struct Event
		{
		private:
			std::vector<Binding<T...>> listeners;

		public:

			//TO- Look at this
			Event<T...>& Invoke(T... args)
			{
				/*for (int i = 0; i < listeners.size(); i += 1)
				{
					listeners[i].Invoke(static_cast<T&&>(args)...);
				}*/

				for (Binding<T...>& l : listeners)
				{
					l.Invoke(static_cast<T&&>(args)...);
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

}