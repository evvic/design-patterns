#pragma once
#include <string>
#include <vector>
using namespace std;

struct ChatRoom;

struct User {
    string name;
    ChatRoom* room{nullptr};
    vector<string> chat_log;

    User(const string &name);

    void say(const string& message) const;
    void pm(const string& who, const string& message) const;

    void receive(const string& origin, const string& message);

    bool operator==(const User &rhs) const;

    bool operator!=(const User &rhs) const;
};


