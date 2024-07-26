#include "user.hpp"
#include "chatroom.hpp"
#include <iostream>

User::User(const string &name) : name(name) {}

void User::say(const string &message) const
{
    room->broadcast(name, message);
}

void User::pm(const string &who, const string &message) const
{
    room->message(name, who, message);
}

void User::receive(const string &origin, const string &message)
{
    string s{origin + ": \"" + message + "\""};
    std::cout << "[" << name << "'s chat session]" << s << "\n";
    chat_log.emplace_back(s);
}

bool User::operator==(const User &rhs) const {
    return name == rhs.name;
}

bool User::operator!=(const User &rhs) const {
    return !(rhs == *this);
}
