#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <cstring>
using namespace std;

/******************************************************
 * FormattedText is an example of NOT using flyweight
 * to optimize storage for duplications.
 * 
 * The boolean array caps is the same length as the 
 * string plain_text and the value at each index
 * corresponds to a character in plain_text being
 * captialized (true) or not (false).
 ******************************************************/
class FormattedText
{
    string plain_text;
    bool *caps;
public:
    explicit FormattedText(const string& plainText)
        : plain_text{plainText}
    {
        caps = new bool[plainText.length()];
        // assure the caps are all initialized as 0
        memset(caps, 0, plain_text.length()); 
    }

    ~FormattedText()
    {
        delete[] caps;
    }

    void capitalize(int start, int end)
    {
        for (int i = start; i <= end; ++i)
            caps[i] = true;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const FormattedText& obj)
    {
        string s;
        for (int i = 0; i < obj.plain_text.length(); ++i)
        {
            char c = obj.plain_text[i];
            s += (obj.caps[i] ? toupper(c) : c);
        }
        return os << s;
    }
};

/******************************************************
 * BetterFormattedText IS an example of using flyweight
 * to optimize storage for duplications.
 * 
 * The boolean array caps is the same length as the 
 * string plain_text and the value at each index
 * corresponds to a character in plain_text being
 * captialized (true) or not (false).
 ******************************************************/
class BetterFormattedText
{
public:
    struct TextRange
    {
        int start, end;
        bool capitalize, bold, italic;

        bool covers(int position) const
        {
            return position >= start && position <= end;
        }
    };

    TextRange& set_range(int start, int end)
    {
        formatting.emplace_back(TextRange{ start, end });
        return *formatting.rbegin();
    }

    explicit BetterFormattedText(const string& plainText)
        : plain_text{plainText}
    {}

    friend std::ostream& operator<<(std::ostream& os, const BetterFormattedText& obj)
    {
        string s;
        for (size_t i = 0; i < obj.plain_text.length(); i++)
        {
            auto c = obj.plain_text[i];
            for (const auto& rng : obj.formatting)
            {
                if (rng.covers(i) && rng.capitalize)
                    c = toupper(c);
                // attempted to add markdown italics formatting...
                if (rng.italic && (rng.start == i or rng.end == i))
                    c = /* '_' + */ toupper(c);
                s += c;
            }
        }
        return os << s;
    }

private:
    string plain_text;
    vector<TextRange> formatting;
};

int main(int argc, char* argv[])
{
    FormattedText ft("This is a brave new world");
    ft.capitalize(10, 15);
    cout << ft << endl;

    BetterFormattedText bft("This is a brave new world");
    bft.set_range(10, 15).capitalize = true;
    cout << bft << endl;
}
