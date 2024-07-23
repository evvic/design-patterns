all: ping pong

ping: ping.cpp
	g++ -std=c++20 -I/usr/include/cpprest ping.cpp -o ping -lcpprest -lboost_system -lcrypto

#-lboost_asio -lboost_asio_ssl

pong: pong.cpp
	g++ -std=c++20 -I/usr/include/cpprest pong.cpp -o pong -lcpprest -lboost_system -lcrypto

# Remove object files
clean: 
	rf -f *.o