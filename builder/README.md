# Builder

## Motivation
- Some objects are simple and can be created in a single constructor call
- But other objects might require a lot of cremony to create
- Having an object with 10 constructor arguments is really not productive
    - Can make mistakes
    - Opt for piece-wise construction when it is complicated
- The builder design allows piece-wise construction to be done through an API

## Builder
- A builder is a separate component for building an object
- Can either give builder a constructor or return it via static function
- To make a builder **fluent**, return `*this`
- Using different facets of an object to build with different builders working in tandem
    - Via a base class

Uniform Initialization