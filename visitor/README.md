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