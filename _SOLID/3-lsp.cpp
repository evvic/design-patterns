#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class Rectangle
{
protected:
    int width, height;
public:
    Rectangle(int width, int height) : width(width), height(height) {}

    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        Rectangle::width=width;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        Rectangle::height=height;
    }

    int area() const {
        return width * height;
    }
};

void process(Rectangle& r)
{
    int w = r.getWidth();
    r.setHeight(10);

    cout << "Area: " << r.area() << endl;
}

int main() {
    cout << "Liskov Substitution Principle" << endl;

    Rectangle r{3 ,4};
    process(r);

    return 0;
}