#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;

enum class OutputFormat
{
    Markdown,
    Html
};

struct ListStrategy
{
    virtual ~ListStrategy() = default;
    virtual void add_list_item(ostringstream& oss, const string& item) {};
    virtual void start(ostringstream& oss) {};
    virtual void end(ostringstream& oss) {};
};

struct MarkdownListStrategy : ListStrategy
{
    void add_list_item(ostringstream& oss, const string& item) override
    {
        oss << " * " << item << endl;
    }
};

struct HtmlListStrategy : ListStrategy
{
    void start(ostringstream& oss) override
    {
        oss << "<ul>" << endl;
    }

    void end(ostringstream& oss) override
    {
        oss << "</ul>" << endl;
    }

    void add_list_item(ostringstream& oss, const string& item) override
    {
        oss << "<li>" << item << "</li>" << endl;
    }
};
