/*****************
 *  Ping Client  *
 *****************/
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

using namespace std;


struct Pingable
{
    virtual ~Pingable() = default;
    virtual wstring ping(const wstring& message) = 0;
};

struct Pong : Pingable
{
    wstring ping(const wstring& message) override
    {
        return message + L" pong";
    }
};


struct RemotePong : Pingable
{
    wstring ping(const wstring& message) override
    {
        wstring result;
        http_client client(U("http://localhost:9149/"));
        uri_builder builder(U("/api/pingpong/"));

        // Append the message as a query parameter
        builder.append_query(U("message"), message);
        
        return client.request(methods::GET, builder.to_string())
            .then([](http_response r) {
                return r.extract_string();
            })
            .then([](const std::string& str) {
                return wstring(str.begin(), str.end());
            })
            .get();
    }
};

void tryit(Pingable& pp)
{
    wcout << pp.ping(L"ping") << "\n";
}


int main()
{
    Pong pp;
    for (int i = 0; i < 3; ++i)
    {
        tryit(pp);
    }
    return 0;
}

