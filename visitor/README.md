# Visitor
- A pattern where a component (visitor) is allowed to traverse the entire inheritance hierarchy
- Implmeneted by propagating a single `visit()` method throughout the entire hierarchy
    - Do not need to touch any other part of the hierarchy

## Motivation
- Need to define a new operation on an entire class hierarchy
    - i.e. make a document model printable to HTML/Markdown
- Do **not** want to keep modifying every class in the hierarchy
- Add extensibility to the side than to an intrusive approach
- Need access ot the non-common aspects of the classes in the hierarchy
- Create an external component to handle rendering
- Avoid type checks
    - Can mostly be built with dynamic casting

## Intrusive Visitor
- Modifies every class in the hierarchy
    - Violates the open-clsoe principle
    - Violates the single responsibility principle
        - Adding new functionality to the classes in the hierarchy is adding another responsibility

#### [`intrusive.cpp`](intrusive.cpp)
```cpp
struct Expression
{
    virtual void print(ostringstream& oss) = 0;
};
```
- The interface `Expression` class will have a virtual `print` method used by all inherited `Expression` classes

```cpp
struct AdditionExpression : Expression
{
    Expression *left, *right;
    // ...

    void print(ostringstream& oss) override {
        oss << "(";
        left->print(oss);
        oss << "+";
        right->print(oss);
        oss << ")";
    }
};
```
- `AdditionExpression` has its `print` recursively call other print methods depending on the obejct type for it's `left` and `right` Expressions

```cpp
auto e = new AdditionExpression{
    new DoubleExpression{1},
    new AdditionExpression{
        new DoubleExpression{2},
        new DoubleExpression{3}
    }
};
ostringstream oss;
e->print(oss);
```
- Calling the visitor that prints the hierarchy of Expressions is simply done with the highest level `print`
- This approach is of course very intrusive and adds another repsonsibility to all Expression-based classes


## Reflective Visitor
- Called **reflective** because in other languages it is called `reflection` for object type checks
    - In C++ this is accomplished with `dynamic_cast`
    - `dynamic_cast` takes time at runtime to check which
```cpp
```
- Try casting it to a DoubleExpression
    - Then format it for that object type
- Else try casting it to a AdditionExpression

- This solution does not scale well with chaining multiple if-statements
- Still better than Intrusive Visitor for not breaking open-close and single responsibility principle

## Classic Visitor (Double Dispatch)
- In C++, it's impossible to form a dispatch at runtime 
- Dispatch: the process of selecting the appropriate code to execute based on certain criteria
    - **Static dispatch**: when the selection occurs at **compile time**
        - C++ mostly operates with the compiler deciding which function to call based on declared types of the variables involved
    - **Dynamic dispatch**: when the selection occurs at **run time**
        - C++ supports a limited form of dynamic dispatch with `virtual` functions
        - When a derived class overrides a virtual function (from a base class), the runtime system determines which version of the function to call
            - Based on the actual type of the object being referenced
        - Also has much more performance overhead at runtime determining the correct function
- **Double dispatch**:

#### [`double-dispatch.cpp`](double-dispatch.cpp)

```cpp
struct Expression
{
    virtual void accept(ExpressionVisitor* visitor) = 0;
};
```
- The base `Expression` class has a virtual accept method that the visitor needs to propogate to all Expression based classes

```cpp
struct DoubleExpression : Expression
{
    double value;
    explicit DoubleExpression(const double value)
        : value{ value } {}

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
    }
};
```
- All 3 classes (`DoubleExpression`, `AdditionExpression`, `SubtractionExpression`) inheriting from Expression will have this **EXACT** same `accept` function
- Although the `accept` function is the same between all of them, the key is that the _`this`_ type passed in will be different based on the object type
    - The type will either be `DoubleExpression`, `AdditionExpression` or `SubtractionExpression`
- That is an example of ONE dynamic dispatch...

```cpp
struct ExpressionVisitor
{
    virtual void visit(DoubleExpression* de) = 0;
    virtual void visit(AdditionExpression* ae) = 0;
    virtual void visit(SubtractionExpression* se) = 0;
};
```
- The second half of the double dispatch is selecting the correct `visit` method based on the object type

```cpp
void ExpressionPrinter::visit(DoubleExpression* de)
{
    oss << de->value;
}
```
- The example `ExpressionPrinter` has a `visit` method for all `Expression` types

#### Running the example
```cpp
auto e = new AdditionExpression{
    new DoubleExpression{ 1 },
    new SubtractionExpression {
        new DoubleExpression{ 2 },
        new DoubleExpression{ 3 }
    }
};
ExpressionPrinter printer;
printer.visit(e);
printer.str();
```
- The Expression is defined with other nested Expressions
- The visitor `ExpressionPrinter` runs `.visit()` on the concrete Expression `e`

## Acyclic Visitor

