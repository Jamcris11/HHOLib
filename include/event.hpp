#ifndef INCLUDE_COMMON_EVENT
#define INCLUDE_COMMON_EVENT

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iterator>
#include <functional>

template <typename... T>
class Event
{
protected:
	std::string mType;
	std::vector<std::function<void(T...)>> mListeners;
public:
	Event() { mType = "undefined"; };
	Event(std::string type) { mType = type; }; 

	/* Adds a listener function to mListeners */
	void AddListener(std::function<void(T...)> listener)
	{
		mListeners.push_back(listener);
	};

	void RemoveListener(std::function<void(T...)> listener)
	{
		typename std::vector<std::function<void(T...)>>::iterator it;

		for (it = mListeners.begin(); it != mListeners.end(); it++) {
			if ((*it) == listener) {
				mListeners.erase(it);
				return;
			}
		}

		throw std::exception("ERR: Cannot remove listener function that isn't "
			"subscribed.");
	};

	void operator+= (std::function<void(T...)> listener)
	{
		AddListener(listener);
	};

	void operator-= (std::function<void(T...)> listener)
	{
		RemoveListener(listener);
	};

	/* Invokes the Event calling all of the listener funtions */
	void Invoke(T... obj)
	{
		for (auto listener : mListeners) {
			listener(obj...);
		}
	};
	
	/* Gets the type of Event */
	std::string Type() { return mType; };
};

#endif // INCLUDE_COMMON_EVENT
