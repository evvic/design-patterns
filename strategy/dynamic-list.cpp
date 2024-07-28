#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include "list-strategy.cpp"
using namespace std;

struct TextProcessor
{
    void clear()
    {
        oss.str("");
        oss.clear();
    }
    void append_list(const vector<string> items)
    {
        list_strategy->start(oss);
        for (auto& item : items)
            list_strategy->add_list_item(oss, item);
        list_strategy->end(oss);
    }

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
    string str() const { return oss.str(); }
private:
    ostringstream oss;
    unique_ptr<ListStrategy> list_strategy;
};

int main()
{
    // markdown
    TextProcessor tp;
    tp.set_output_format(OutputFormat::Markdown);
    tp.append_list({"foo", "bar", "baz"});
    cout << tp.str() << endl;

    // html
    tp.clear();
    tp.set_output_format(OutputFormat::Html);
    tp.append_list({"foo", "bar", "baz"});
    cout << tp.str() << endl;

    return 0;
}
