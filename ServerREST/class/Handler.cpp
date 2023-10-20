#include "Handler.hpp"
#include "RequestUtil.hpp"

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
void Handler::handle_get(http_request request)
{
    cout << U("GET request message: ") << request.to_string() << endl;

    RequestUtil::DisplaySplitedRequestPath(&request);

    const utility::string_t key("request");
    const utility::string_t request_message = RequestUtil::GetDataInQuery(&request, key);

    // get developer by id
    if(request_message == U("get_developer_by_id")) {
        _controller.GetDeveloperById(&request);
    }
    // get all developers
    else if(request_message == U("get_all_developers")) {
        _controller.GetAllDevelopers(&request);
    }
    else {
        Http_Request_Error error;
        error.http_error_code = status_codes::Forbidden;
        error.errorMessage = U("Forbidden: Unrecognized request");
        request.reply(status_codes::Forbidden, error.AsJSON()).then([=](pplx::task<void> t) {
            handle_error(t);
        });
        cout << "Error: " << error.http_error_code << " " << error.errorMessage << endl;
        return;
    }

    return;
}

/**
* PUT
*/
void Handler::handle_put(http_request request)
{
    cout <<  "PUT request message: " << request.to_string() << endl;

    const utility::string_t key("request");
    const utility::string_t request_message = RequestUtil::GetDataInQuery(&request, key);

    // update developer
    if(request_message == U("update_developer")) {
        _controller.UpdateDeveloper(&request);
    }
    else {
        Http_Request_Error error;
        error.http_error_code = status_codes::Forbidden;
        error.errorMessage = U("Forbidden: Unrecognized request");
        request.reply(status_codes::Forbidden, error.AsJSON()).then([=](pplx::task<void> t) {
            handle_error(t);
        });
        cout << "Error: " << error.http_error_code << " " << error.errorMessage << endl;
        return;
    }
}

/**
* POST
*/
void Handler::handle_post(http_request request)
{
    cout <<  "POST request message: " << request.to_string() << endl;

    const utility::string_t key("request");
    const utility::string_t request_message = RequestUtil::GetDataInQuery(&request, key);

    // adding developer
    if(request_message == U("add_developer")) {
        _controller.AddDeveloper(&request);
    }
    else {
        Http_Request_Error error;
        error.http_error_code = status_codes::Forbidden;
        error.errorMessage = U("Forbidden: Unrecognized request");
        request.reply(status_codes::Forbidden, error.AsJSON()).then([=](pplx::task<void> t) {
            handle_error(t);
        });
        cout << "Error: " << error.http_error_code << " " << error.errorMessage << endl;
        return;
    }
}

/**
* DELETE
*/
void Handler::handle_delete(http_request request)
{
    cout << U("DELETE request message: ") << request.to_string() << endl;

    const utility::string_t key("request");
    const utility::string_t request_message = RequestUtil::GetDataInQuery(&request, key);

    if(request_message == U("delete_developer_by_id")) {
        _controller.DeleteDeveloperById(&request);
    }
    else {
        Http_Request_Error error;
        error.http_error_code = status_codes::Forbidden;
        error.errorMessage = U("Forbidden: Unrecognized request");
        request.reply(status_codes::Forbidden, error.AsJSON()).then([=](pplx::task<void> t) {
            handle_error(t);
        });
        cout << "Error: " << error.http_error_code << " " << error.errorMessage << endl;
        return;
    }
}

/**
* Handle error
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
