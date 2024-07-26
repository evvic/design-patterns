#include "user.hpp"
#include "chatroom.hpp"

int main()
{
    ChatRoom room;

    User john{"John"};
    User jane{"Jane"};
    room.join(&john);
    room.join(&jane);
    john.say("hi room");
    jane.say("oh, hey john");

    User simon{"Simon"};
    room.join(&simon);
    simon.say("hi everyone!");

    jane.pm("Simon", "glad you found us, simon!");

    return 0;
}