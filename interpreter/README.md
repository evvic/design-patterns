# Interpreter
> Less of a design pattern and more of a separate branch on computer science... <br>
> Designing parsers and constructing output
- A component that process structured text data
    - Does so by turning it into separate lexical tokens (lexing)
    - Then interpreting sequences of said tokens (parsing)

- (Textual) input that needs to be processed
- Code/text needs to be processed and turned into an object oriented program
- i.e. HTML, YAML, redular expresions, etc...

## Interpreter Example
#### [`numexpr.cpp`](numexpr.cpp) _Numerical Expression interpreter program_

### Lexing
- The process of taking the input and tokenizing it into something machine understandable

#### Token
```cpp
struct Token {
    enum Type { integer, plus, minus, lparen, rparen } type;
    string text;

    explicit Token(Type type, const string& text) :
        type{type}, text{text} {}
    // ...
```
- A token struct is made to hold the type of value and the captured string of it
- In this example the `Token` cannot handle all arithgmetic operators

```cpp
vector<Token> lex(const string& input)
{
    vector<Token> result;

    for (int i = 0; i < input.size(); ++i)
    {
        switch (input[i])
        {
        case '+':
            result.push_back(Token{ Token::plus, "+" });
            break;
        case '-':
            result.push_back(Token{ Token::minus, "-" });
            break;
        case '(':
            result.push_back(Token{ Token::lparen, "(" });
            break;
        case ')':
            result.push_back(Token{ Token::rparen, ")" });
            break;
        default:
            // handle numbers...
    }
    return result;
}
```
- The function `lex()` takes a string and parses it into a vector of tokens

### Parser

