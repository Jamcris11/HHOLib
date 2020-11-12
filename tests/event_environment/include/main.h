#ifndef INCLUDE_MAIN
#define INCLUDE_MAIN

#include <hho/event.hpp>
#include <string>
#include <functional>
#include <chrono>

static Event<int> OnMessage;
static EventBus<int> Queue;

void PrintMessage(int v);

class A
{
public:
        void B(int v)
        {
                std::cout << v << '\n';
        }
};

int main();

#endif // INCLUDE_MAIN
