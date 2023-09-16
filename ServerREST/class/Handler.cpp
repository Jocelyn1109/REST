#include <vector>
#include <exception>
#include <map>
#include "Handler.hpp"
#include "Data.hpp"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

Handler::Handler()
{
    //ctor
}

Handler::Handler(utility::string_t url):m_listener(url)
{
    m_listener.support(methods::GET, bind(&Handler::handle_get, this, placeholders::_1));
    m_listener.support(methods::PUT, bind(&Handler::handle_put, this, placeholders::_1));
    m_listener.support(methods::POST, bind(&Handler::handle_post, this, placeholders::_1));
    m_listener.support(methods::DEL, bind(&Handler::handle_delete, this, placeholders::_1));
}

Handler::~Handler()
{
    //dtor
}

/**
* GET
*/
void Handler::handle_get(http_request message)
{
    cout << U("GET request message: ") << message.to_string() << endl;
    cout << U("Relative URI ") << message.relative_uri().to_string() << endl;

    vector<utility::string_t> paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));
    for(auto it1 = paths.begin(); it1!=paths.end(); it1++) {
        cout << U("Path") << U(" ") << *it1 << endl;
    }

    map<utility::string_t, utility::string_t> query = http::uri::split_query(http::uri::decode(message.relative_uri().query()));
    for(auto it2 = query.begin(); it2!=query.end(); it2++) {
        cout << U("Query") << U(" ") << it2->first << U(" ") << it2->second << endl;
    }

    auto queryItr = query.find(U("request"));
    utility::string_t request = queryItr->second;
    cout << U("Request") << U(" ") << request << endl;

    if(request == U("get_developers")) {

        DataPeople dataPeople;
        dataPeople.job = ("Developers");

        People p1;
        p1.age = 25;
        p1.name = U("Jack");
        dataPeople.peoples.push_back(p1);

        People p2;
        p2.age = 20;
        p2.name = U("John");
        dataPeople.peoples.push_back(p2);

        utility::string_t response = dataPeople.AsJSON().serialize();
        cout << "Reponse: " << response << endl;

        message.reply(status_codes::OK, dataPeople.AsJSON()).then([=](pplx::task<void>t) {
            try {
                t.get();
            }
            catch(const std::exception &e) {
                cout << "Error exception: " << e.what() << endl;
            }
        });

        return;
    }
    else {
        Http_Request_Error error;
        error.http_error_code = status_codes::Forbidden;
        error.errorMessage = U("Forbidden: Unrecognized request");
        message.reply(status_codes::Forbidden, error.AsJSON()).then([](pplx::task<void> t) {
            try {
                t.get();
            }
            catch (const std::exception &e) {
                cout << "Error exception: " << e.what() << endl;
            }
        });
        cout << "Error: " << error.http_error_code << " " << error.errorMessage << endl;
        return;
    }


    return;
}

/**
* PUT
*/
void Handler::handle_put(http_request message)
{
    ucout <<  "PUT request message: " << message.to_string() << endl;
    string rep = U("PUT request response");
    message.reply(status_codes::OK,rep);
}

/**
* POST
*/
void Handler::handle_post(http_request message)
{
    ucout <<  "POST request message: " << message.to_string() << endl;
    string rep = U("POST request response");
    message.reply(status_codes::OK,rep);
}

/**
* DELETE
*/
void Handler::handle_delete(http_request message)
{
    ucout <<  "DELETE request message: " << message.to_string() << endl;
    string rep = U("DELETE request response");
    message.reply(status_codes::OK,rep);
}

/**
* handle error
*/
void Handler::handle_error(pplx::task<void>& t)
{
    try {
        t.get();
    }
    catch (const std::exception &e) {
        cout << "Error exception: " << e.what() << endl;
    }
}
