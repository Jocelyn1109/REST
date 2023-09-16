#include <iostream>
#include "Common.hpp"
#include "Handler.hpp"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<Handler> g_httpHandler;

void initialize_handler(const string_t& address)
{
    uri_builder uri(address);
    string_t addr = uri.to_uri().to_string();
    g_httpHandler = std::unique_ptr<Handler>(new Handler(addr));
    g_httpHandler->open().wait();

    ucout << string_t(U("Listening for request at: ")) << addr << endl;
}

void shutdown_handler()
{
    g_httpHandler->close().wait();
}


int main(int argc, char *argv[])
{
    cout << "REST server C++" << endl;
    utility::string_t port = U("34568");
    if(argc == 2) {
        port = argv[1];
    }

    utility::string_t address = U("http://127.0.0.1:");
    address.append(port);

    initialize_handler(address);

    cout << "Press ENTER to exit." << endl;

    string line;
    getline(cin, line);

    shutdown_handler();

    return 0;
}
