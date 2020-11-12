#ifndef INCLUDE_COMMON_EVENT
#define INCLUDE_COMMON_EVENT

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iterator>
#include <functional>
#include <tuple>
#include <queue>

template <typename... T>
class ListenerHandler
{
protected:
	std::vector<std::function<void(T...)>> mListeners;
public:
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
};

template <typename... T>
class Event : public ListenerHandler<T...>
{
protected:
	std::string mType;
public:
	Event() { mType = "undefined"; };
	Event(std::string type) { mType = type; }; 

	/* Invokes the Event calling all of the listener funtions */
	void Invoke(T... obj)
	{
		for (auto listener : this->mListeners) {
			listener(obj...);
		}
	};
	
	/* Gets the type of Event */
	std::string Type() { return mType; };
};

template <typename... T>
class EventBus : public ListenerHandler<T...>
{
private:
	std::queue<std::tuple<T...>> queue;

	std::tuple<T...> VariadicToTuple(T... args)
	{
		return std::tuple<T...>(args...);
	};

public:
	void BindEvent(Event<T...>& event)
	{
		auto f = std::bind(&EventBus::Store, this, std::placeholders::_1);
		event.AddListener(f);
	};

	void Store(T... args)
	{
		queue.push(VariadicToTuple(args...));
	};

	void Next()
	{
		for (auto listener : this->mListeners) {
			std::apply(listener, queue.front());
		}

		queue.pop();
	};
};

#endif // INCLUDE_COMMON_EVENT
