# Adapter
- A construct which adapts an existing interface X to confrom to the required interface Y
- Using and adapter to connect two interfaces
- Determine the API you have and the API you need

## Motivation
- Need an adapter to give the interface required from the interface available

## Adapter Example
- This example is to convert an object `Line` to a `vector<Point>`
    - Where `Line` has a start and end `Point`
    - and should be turned into an actual vector of Points that conncet start and end
    - `struct Point {int x, int y;};`
```cpp
struct LineToPointAdapter {
    LineToPointAdapter(Line& line) {
        // Math to get coordinate in the line and convert to a Point...
        int x = 0;
        int y = 0;
        // Add Point to vector..
        points.emplace_back(Point{ x ,y })
    }
    virtual vector<Point>::iterator begin() {
        return points.begin()
    }
    virtual vector<Point>::iterator end() {
        return points.end()
    }
private:
    vector<Point> points;
}
```
- The above example does not contain all the logic
    - But it shows an idea of an adapter
- The constructor is converting a Line object into a `vector<Point>` 

```cpp
LineToPointAdapter lpo {line};
DrawPoints(dc, lpo.begin(), lpo.end());
```
- To use the adapter to `DrawPoints` just construct the `LineToPointAdapter` object
    - The object takes in a line and converts it to a `vector<Point>`
- Then `DrawPoints` uses the begin and end iterators to get all the Point values

## Caching
- Intermediate representations can take up a lot of space
- Use caching and other optimizations to reduce redeundant adaptions