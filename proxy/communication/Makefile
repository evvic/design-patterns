all: ping pong

ping: ping.cpp
	g++ -std=c++20 -I/usr/include/cpprest ping.cpp -o ping

pong: pong.cpp
	g++ -std=c++20 -I/usr/include/cpprest pong.cpp -o pong

# Remove object files
clean: 
	rf -f *.o