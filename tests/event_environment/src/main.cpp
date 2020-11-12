#include "main.h"

void PrintMessage(int num)
{
        std::cout << num << '\n';
}

int main()
{
        auto start = std::clock();

        A test;

        Queue.BindEvent(OnMessage);
        //std::function<void(int)> f = ;
        Queue += { &A::B, test };

        std::string str { "Hello" };

        for (int i = 0; i < 100000; ++i) {
                OnMessage.Invoke(10);
        }

        while (Queue.Next());

        std::cout << 1000 * (std::clock() - start) / CLOCKS_PER_SEC << " ms";

        return 0;
}