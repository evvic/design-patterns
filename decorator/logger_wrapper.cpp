/************************************************
 * Defines a Logger struct that wraps around any
 * function provided so methods can be done 
 * before and after the function call 
 ************************************************/
#include <string>
#include <iostream>
#include <sstream>
#include <functional>
using namespace std;

// need partial specialization for this to work
template <typename> struct Logger;

// return type and argument list
template <typename R, typename... Args> 
struct Logger<R(Args...)>
{
    Logger(function<R(Args...)> func, const string& name)
        : func{func}, name{name}
    {}

    R operator() (Args ...args)
    {
        cout << "Entering " << name << endl;
        R result = func(args...);
        cout << "Exiting " << name << endl;
        return result;
    }

    function<R(Args ...)> func;
    string name;
};

template <typename R, typename... Args>
auto make_logger(R (*func)(Args...), const string& name)
{
    return Logger<R(Args...)>(std::function<R(Args...)>(func), name);
}

double add(double a, double b)
{
    cout << a << "+" << b << "=" << (a + b) << endl;
    return a + b;
}

int main() {
    auto logged_add = make_logger(add, "Add");
    auto result = logged_add(2, 3);
}
