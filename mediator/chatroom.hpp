#pragma once
#include <algorithm>
#include <string>
#include <vector>
// #include <user.hpp>
using namespace std;

struct User;

struct ChatRoom
{
    vector<User*> users;

    void broadcast(const string& origin, const string& message);

    void join(User* p);

    void message(
        const string& origin,
        const string& who,
        const string& message
    );
};
