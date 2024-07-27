SOURCES = main.cpp observer.hpp saferobservable.hpp
EXTRA = observable.hpp

observer: $(SOURCES)
	g++ -std=c++20 $(SOURCES) -o observer

# Remove object files
clean: 
	rf -f *.o