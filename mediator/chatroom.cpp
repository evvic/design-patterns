#include "user.hpp"
#include "chatroom.hpp"

void ChatRoom::broadcast(const string &origin, const string &message)
{
    for (auto u : users)
        if (u->name != origin)
            u->receive(origin, message);
}

void ChatRoom::join(User *u)
{
    string join_msg = u->name + " joins the chat";
    broadcast("room", join_msg);
    u->room = this;
    users.push_back(u);
}

void ChatRoom::message(
    const string& origin,
    const string& who,
    const string& message)
{
    auto target = std::find_if(
        begin(users),
        end(users),
        [&](const User *u) { return u->name == who;
    });

    if (target != end(users))
    {
        (*target)->receive(origin, message);
    }
}
