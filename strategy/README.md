# Strategy
> aka the Policy Pattern

- Enables the exact behaviour of a system to be selected either at run-time (dynamic) or compile-time (static)
- Allows to partially specify the behaviour of the system then augment it later on

## Motivation
- Many algorithms can be decomposed into higher-and-lower level parts
- The high-level (or generic) part of the algorithm can be reused for other algorithms with similar parts

## Dynamic Strategy
- Render a list of elements in either Markdown or HTML using the Dynamic Strategy pattern
#### [`dynamic-list.cpp`](dynamic-list.cpp)

```cpp
enum class OutputFormat
{
    Markdown,
    Html
};
```
- Enum the 2 methods

```cpp
struct ListStrategy
{
    virtual ~ListStrategy() = default;
    virtual void add_list_item(ostringstream& oss, const string& item) {};
    virtual void start(ostringstream& oss) {};
    virtual void end(ostringstream& oss) {};
};
```
- `ListStrategy` is a virtual class that has all its default member functions do nothing
- This is ideal because the Mardown and HTML list renderers may not need to implement all these functions
    - Although `add_list_item` could be purely virtual because it is required by both Markdown and HTML strategy

#### Dynamic TextProcessor
```cpp
struct TextProcessor {
    // ...
unique_ptr<ListStrategy> list_strategy;
void set_output_format(const OutputFormat format)
    {
        switch(format)
        {
        case OutputFormat::Markdown: 
            list_strategy = make_unique<MarkdownListStrategy>();
            break;
        case OutputFormat::Html: 
            list_strategy = make_unique<HtmlListStrategy>();
            break;
        default:
            throw runtime_error("Unsupported strategy.");
        }
    }
```
- TextProcessor allow us to use a particular strategy in order to print a formatted list of items
- 2 approaches to this strategy pattern:
    - Dynamic approach: A variable of a strategy type
        - (using this method here)
    - Static approach: take the type as a template argument
- Update the `list_strategy` to based on the `set_output_format` switch statement
    - The 2 options are:
        - `MarkdownListStrategy`: inherits from `ListStrategy` and overrides:
            - `add_list_item`: Prefixes list item with ` * `
        - `HtmlListStrategy`: inherits from `ListStrategy` and overrides:
            - `start`: adds the opening list start tag `<ul>`
            - `end`: adds the closing list end tag `</ul>`
            - `add_list_item`: adds the list item with its tags `<li> ... </li>`

