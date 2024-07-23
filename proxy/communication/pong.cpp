/******************
 * Pong Webserver *
 ******************/
#include <iostream>
#include <string>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/filestream.h>

using namespace web;
using namespace web::http;
using namespace concurrency::streams;
using namespace web::http::experimental::listener;          // HTTP client features

using namespace std;

// Define a simple interface for handling messages
struct Pongable {
    virtual wstring ping(const wstring& message) = 0;
};

// Implementation returning "Pong" for any message
struct BasicPong : Pongable {
    wstring ping(const wstring& message) override {
        return message + L" pong";
    }
};

// Function to handle HTTP GET requests
void handle_get(http_request request) {
    // Extract the message from the query string (if any)
    auto message = request.request_uri().query();
    //.at(U("message"));

    // Call the ping method and get the response
    // wstring response = message + L" pong";

    // Create a JSON response object
    //   json::value json_response;
    //   json_response[U("message")] = response;

    utf8string resp = "Pong";
        

    // Send the JSON response with status code 200 (OK)
    request.reply(status_codes::OK, resp);
}

int main() {
    // Create an instance of the Pong implementation
    BasicPong pong;

    const string webserver = "http://localhost:8080/";

    // Define the listening address and port
    utility::string_t address = U(webserver);

    // Create an HTTP listener
    http_listener listener(address);

    // Register the GET request handler
    listener.support(methods::GET, handle_get);

    // Start listening for requests
    listener.open().wait();
    std::wcout << L"Listening for requests on ";
    cout  << webserver << std::endl;

    // Wait for a user to press Enter to stop the server
    std::getchar();

    // Close the listener
    listener.close().wait();

    return 0;
}
