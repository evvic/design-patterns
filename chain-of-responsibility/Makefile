all: cards broker

broker: broker.cpp
	g++ -std=c++20 broker.cpp -o broker

cards: cards.cpp
	g++ -std=c++20 cards.cpp -o cards

# Remove object files
clean: 
	rf -f *.o
