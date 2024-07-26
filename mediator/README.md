# Mediator
- Fascilitates communication between components
    - Without them necessarily being aware of each other
    - Or having direct (reference) acces to each other

## Motivation
- Components may go in and out of the system at anytime
    - i.e. chat room or online game
- It makes no sense for the components to have direct reference to one another
    - These references could be deleted
- Therefore having them refer to a central componenet ("mediator") that fascilitates communication

## Chat Room Example
#### [`main.cpp`](main.cpp) [`chatroom.hpp`](chatroom.hpp) [`user.hpp`](user.hpp)

### User Class

```cpp
struct User {
    string name;
    ChatRoom* room{nullptr};
    vector<string> chat_log;
    // ...
```
- Every person connecting to the chatroom joins as a `User` object
- The ChatRoom room points to the room the person is connected to

```cpp
User::User(const string &name);

void User::say(const string& message) const;
void User::pm(const string& who, const string& message) const;
```
- The 2 functions the users get is to:
    - `say` a message as a broadcast to all connected users
    - `pm` a message a single user only

```cpp
void User::receive(const string& origin, const string& message);
```
- Get message from another user or service messages from the room

### Chat Room Class
```cpp
struct ChatRoom
{
    vector<User*> users;
// ...
```
- The `ChatRoom` only holds a vector of `User`s

```cpp
void ChatRoom::join(User *u)
{
    string join_msg = u->name + " joins the chat";
    broadcast("room", join_msg);
    u->room = this;
    users.push_back(u);
}
```
- When a new `User` is joining the chat room they are added to the `ChatRoom` vector of `User`s
- The new `User` object `u` has it's `room` variable point to `this` `ChatRoom` object
- A broadcast message is sent out to all Users in the chat room that the new user joined

```cpp
void ChatRoom::broadcast(const string &origin, const string &message)
{
    for (auto u : users)
        if (u->name != origin)
            u->receive(origin, message);
}
```
- When a `User` wants to broadcast, the `ChatRoom::broadcast` method is invoked
- It iterates through all users and sends the message
    - It skips the use rthat originally sent the message

```cpp
void ChatRoom::message(const string& origin, const string& who, const string& message)
{
    auto target = std::find_if(
        begin(users),
        end(users),
        [&](const User *u) { return u->name == who; }
    );

    if (target != end(users))
    {
        (*target)->receive(origin, message);
    }
}
```
- `message` is used to fascilitate private messaging between 2 users
- `std::find_if` iterrates through the users vector
    - The lambda returns bool on whether it found the target user
    - The `[&]` captures all current variables as context **by reference**

