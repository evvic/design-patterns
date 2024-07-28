all: handmade msm

handmade: handmade.cpp
	g++ -std=c++20 handmade.cpp -o handmade

msm: msm.cpp
	g++ -std=c++20 msm.cpp -o msm

# Remove object files
clean: 
	rf -f *.o
