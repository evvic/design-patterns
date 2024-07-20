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

    virtual void setWidth(int width) {
        Rectangle::width=width;
    }

    int getHeight() const {
        return height;
    }

    virtual void setHeight(int height) {
        Rectangle::height=height;
    }

    int area() const {
        return width * height;
    }
};

// inherit rectangle to make a square
// the sides are set together for a square
class Square : public Rectangle
{
public:
    Square(int size) : Rectangle(size, size) {}

    void setWidth(int width) override {
        this->width = this->height = width;
    }

    void setHeight(int height) override {
        this->width = this->height = height;
    }


};

struct RectangleFactory
{
    static Rectangle create_rectangle(int w, int h)
    {
        return Rectangle(w, h);
    }
    static Rectangle create_square(int size)
    {
        return Rectangle(size, size);
    }
};


// change a side and check the area
void process(Rectangle& r)
{
    int change = 10;
    int w = r.getWidth();
    r.setHeight(change);

    cout << "Expected area: " << change*w << ", got " << r.area() << endl;
}

int main() {
    cout << "Liskov Substitution Principle" << endl;

    Rectangle r{3 ,4};
    process(r);

    // Creating a square from the Square class that inherits from Rectangle
    // will cause unexpected errors in process! Broken the Liskov Substitution
    // Principle!!

    Square sq{5};
    process(sq);

    // It doesnt necessarily make sense to have Square class inherit from Rectangle class

    // Using a factory to create Rectangles and Squares allows the Rectangle "subtype"
    // to not break anything
    Rectangle sq2 = RectangleFactory::create_square(5);
    process(sq2);

    return 0;
}