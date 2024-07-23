# Communication Proxy
- Communication proxy abstracts the communication work out of the interface
    - So it appears like the typical interface (but doing some sort of communication work behind the scenes)

## C++ Webserver Example

- Running the server and client programs on Ubuntu
- Requiring installing these packages
```bash
sudo apt install libcpprest-dev libxmu-dev libxmu-headers freeglut3-dev libxext-dev libxi-dev
```

#### [`ping.cpp`](ping.cpp)
- Sends a "ping" message to the webserver [hardcoded]
- Run `./ping` to ping the webserver

#### [`pong.cpp`](pong.cpp)
- Listening for a request
    - Replied with a "pong" message to the client [hardcoded]
- Run `./pong` to start the webserver