# Strategy
> aka the Policy Pattern

- Enables the exact behaviour of a system to be selected either at run-time (dynamic) or compile-time (static)
- Allows to partially specify the behaviour of the system then augment it later on

## Implementation
- Define an algorithm at a high level
- Define the interface you expect each strategy to follow 
- Provide either dynamic or static composition of the strategy in the overall algorithm

## Motivation
- Many algorithms can be decomposed into higher-and-lower level parts
- The high-level (or generic) part of the algorithm can be reused for other algorithms with similar parts

## Dynamic Strategy
- Render a list of elements in either Markdown or HTML using the Dynamic Strategy pattern
#### [`list-strategy.cpp`](list-strategy.cpp)
- **Methods in [`list-strategy.cpp`](list-strategy.cpp) are used for dynamic and static strategy**

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

#### Dynamic TextProcessor [`dynamic-list.cpp`](dynamic-list.cpp) 
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

## Static Strategy
- Using the same objects in [`list-strategy.cpp`](list-strategy.cpp) as dynamic strategy

#### Static TextProcessor [`static-list.cpp`](static-list.cpp) 
```cpp
template <typename LS>
struct TextProcessor
{
    LS list_strategy;
    void append_list(const vector<string> items)
    {
        list_strategy.start(oss);
        for (auto& item : items)
            list_strategy.add_list_item(oss, item);
        list_strategy.end(oss);
    }
```
- Very similar to dynamic strategy except its using templating to determine the correct `list_strategy` to use in `TextProcessor`
    - Therefore it does not have the function `set_output_format()`
- Does not have the ability to switch the strategy at runtime

