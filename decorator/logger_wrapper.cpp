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
// incomplete template declaration
template <typename> struct Logger;

// template
// @param typename RetType: the return type of the function
// @param typename... Args: a variable number of template function arguments
template <typename RetType, typename... Args> 
struct Logger<RetType(Args...)>
{
    Logger(function<RetType(Args...)> func, const string& name)
        : func{func}, name{name}
    {}

    // operator overload for providing functions arguments
    // and invokes the function
    RetType operator() (Args ...args)
    {
        cout << "Entering " << name << endl;
        RetType result = func(args...);
        cout << "Exiting " << name << endl;
        return result;
    }

    function<RetType(Args ...)> func;
    string name;
};

// template
// @param typename RetType: the return type of the function
// @param typename... Args: a variable number of template function arguments
template <typename RetType, typename... Args>
// @param RetType (*func)(Args...): function pointer 
// @param string name: function label
// @return Logger<RetType(Args...)> object with created function and name label
auto make_logger(RetType (*func)(Args...), const string& name)
{
    // use std::function to build the function object from the func pointer
    auto built_func = std::function<RetType(Args...)>(func);
    return Logger<RetType(Args...)>(built_func, name);
}

double add(double a, double b)
{
    cout << a << "+" << b << "=" << (a + b) << endl;
    return a + b;
}

int main() {
    auto logged_add = make_logger(add, "Add");
    double result = logged_add(2, 3);
    cout << "Result: " << result << endl;
}
