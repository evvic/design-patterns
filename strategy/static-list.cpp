#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;
#include "list-strategy.cpp"

template <typename LS>
struct TextProcessor
{
    void clear()
    {
        oss.str("");
        oss.clear();
    }
    void append_list(const vector<string> items)
    {
        list_strategy.start(oss);
        for (auto& item : items)
            list_strategy.add_list_item(oss, item);
        list_strategy.end(oss);
    }
    string str() const { return oss.str(); }
private:
    ostringstream oss;
    LS list_strategy;
};

int main()
{
    // markdown
    TextProcessor<MarkdownListStrategy> tpm;
    tpm.append_list({"foo", "bar", "baz"});
    cout << tpm.str() << endl;

    // html
    TextProcessor<HtmlListStrategy> tph;
    tph.append_list({"foo", "bar", "baz"});
    cout << tph.str() << endl;

    return 0;
}
