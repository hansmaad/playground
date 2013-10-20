
#include <iostream>
#include <future>
#include <chrono>

#include "model.hpp"


struct SimpleModel
{   
    SimpleModel(double result) : result(result)
    {
        std::cout << "ctor(double)\n";
    }

    SimpleModel(const SimpleModel& m)
        : result(m.result)
    {
        std::cout << "ctor(SimpleModel)\n";
    }

    SimpleModel(SimpleModel&& m) noexcept
        : result(m.result)
    {
        std::cout << "ctor(SimpleModel&&)\n";
    }

    void operator=(SimpleModel& m) noexcept
    {
        result = m.result;
        std::cout << "=(SimpleModel&)\n";
    }

    void operator=(SimpleModel&& m) noexcept
    {
        result = m.result;
        std::cout << "=(SimpleModel&&)\n";
    }

    ~SimpleModel() noexcept
    {
        std::cout << "dtor\n";
    }

    double Calculate(const Duct& duct)
    {
        std::cout << "Simple\n";
        return result;
    }
    double result;
};


int main()
{  
    using namespace std;

    Model m(SimpleModel(3.14));
    m.Calculate(Duct());
    m.Calculate(Duct());

    cout << "Hello World!\n";

}

