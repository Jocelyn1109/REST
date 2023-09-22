#include "RestController.hpp"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

RestController::RestController()
{
    //ctor
}

RestController::~RestController()
{
    //dtor
}

/**
* handle error
*/
void RestController::handle_error(pplx::task<void>& t)
{
    try {
        t.get();
    }
    catch (const std::exception &e) {
        cout << "Error exception: " << e.what() << endl;
    }
}
