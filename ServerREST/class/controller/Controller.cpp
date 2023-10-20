#include <string>
#include <map>
#include <exception>
#include "Controller.hpp"
#include "RequestUtil.hpp"
#include "data/dto/DeveloperDto.hpp"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

Controller::Controller()
{
    //ctor
}

Controller::~Controller()
{
    //dtor
}

/**
* GET developer by id
*/
void Controller::GetDeveloperById(const web::http::http_request *request)
{
    if(request == nullptr) {
        cerr << "Request null" << endl;
        request->reply(status_codes::InternalError, U("Internal Server Error")).then([=](pplx::task<void>t) {
            handle_error(t);
        });
    }
    else {

        try {
            const utility::string_t key("id");
            const utility::string_t id_str = RequestUtil::GetDataInQuery(request, key);
            People developer;
            web::json::value json_developer;
            cout << "Get developer by id: " << id_str << endl;

            if(!id_str.empty()) {
                int id = stoi(id_str);
                DeveloperDto * pDeveloperDto = _service.GetDeveloperById(id);
                json_developer = pDeveloperDto->AsJSON();
                cout << "Developer: " << pDeveloperDto->AsJSON().serialize() << endl;
                delete pDeveloperDto;
            }

            request->reply(status_codes::OK, json_developer).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }
        catch(exception const &ex) {
            cerr << ex.what() << endl;
            request->reply(status_codes::InternalError, U("Internal Server Error")).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }
    }
}

/**
* GET all developers
*/
void Controller::GetAllDevelopers(const web::http::http_request *request)
{
    if(request == nullptr) {
        cerr << "Request null" << endl;
        request->reply(status_codes::InternalError, U("Internal Server Error")).then([=](pplx::task<void>t) {
            handle_error(t);
        });
    }
    else {

        try {
            DevelopersDto * pDevelopersDto = _service.GetAllDevelopers();

            cout << "Get all developers: " << pDevelopersDto->AsJSON().serialize() << endl;

            request->reply(status_codes::OK, pDevelopersDto->AsJSON()).then([=](pplx::task<void>t) {
                handle_error(t);
            });

            delete pDevelopersDto;
        }
        catch(exception const &ex) {
            cerr << ex.what() << endl;
            request->reply(status_codes::InternalError, U("Internal Server Error")).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }


    }
}

/**
* POST add developer
*/
void Controller::AddDeveloper(const web::http::http_request *request)
{
    if(request == nullptr) {
        cerr << "Request null" << endl;
        request->reply(status_codes::InternalError, U("Internal Server Error")).then([=](pplx::task<void>t) {
            handle_error(t);
        });
    }
    else {

        try {
            web::json::value json_developer = request->extract_json(true).get();
            cout << "Adding new developer: " << json_developer.serialize() << endl;
            DeveloperDto developerDto = DeveloperDto::FromJson(json_developer.as_object());
            _service.AddDeveloper(developerDto);

            request->reply(status_codes::OK, U("Developer added")).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }
        catch(json::json_exception &ex) {
            cout << "Invalid json object" << endl;
            request->reply(status_codes::InternalError, U("Invalid json object")).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }
        catch(exception const &ex) {
            cerr << ex.what() << endl;
            request->reply(status_codes::InternalError, U("Internal Server Error")).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }
    }
}

/**
* UPDATE update developer
*/
void Controller::UpdateDeveloper(const web::http::http_request *request)
{
    if(request == nullptr) {
        cerr << "Request null" << endl;
        request->reply(status_codes::InternalError, U("Internal Server Error")).then([=](pplx::task<void>t) {
            handle_error(t);
        });
    }
    else {
        try {
            web::json::value json_developer = request->extract_json(true).get();
            cout << "Update developer: " << json_developer.serialize() << endl;
            DeveloperDto developerDto = DeveloperDto::FromJson(json_developer.as_object());
            _service.UpdateDeveloper(developerDto);

            request->reply(status_codes::OK, U("Developer updated")).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }
        catch(json::json_exception &ex) {
            cout << "Invalid json object" << endl;
            request->reply(status_codes::InternalError, U("Invalid json object")).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }
        catch(exception const &ex) {
            cerr << ex.what() << endl;
            request->reply(status_codes::InternalError, U("Internal Server Error")).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }
    }
}

/**
* DELETE developer
*/
void Controller::DeleteDeveloperById(const web::http::http_request *request)
{
    if(request == nullptr) {
        cerr << "Request null" << endl;
        request->reply(status_codes::InternalError, U("Internal Server Error")).then([=](pplx::task<void>t) {
            handle_error(t);
        });
    }
    else {

        try {
            const utility::string_t key("id");
            const utility::string_t id_str = RequestUtil::GetDataInQuery(request, key);
            cout << "Delete developer with id: " << id_str << endl;

            int id = stoi(id_str);
            _service.DeleteDeveloperById(id);

            request->reply(status_codes::OK, U("User deleted")).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }
        catch(exception const &ex) {
            cerr << ex.what() << endl;
            request->reply(status_codes::InternalError, U("Internal Server Error")).then([=](pplx::task<void>t) {
                handle_error(t);
            });
        }
    }
}

/**
* Handle error
*/
void Controller::handle_error(pplx::task<void>& t)
{
    try {
        t.get();
    }
    catch (const std::exception &e) {
        cout << "Error exception: " << e.what() << endl;
    }
}
