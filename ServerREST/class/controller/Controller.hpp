/**
* Controller REST
* @author: Jocelyn GIROD
* @date: Septembre 2023
*/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Common.hpp"
#include "Data.hpp"
#include "Service.hpp"

class Controller {
public:
    Controller();
    virtual ~Controller();

    void GetDeveloperById(const web::http::http_request *request);
    void GetAllDevelopers(const web::http::http_request *request);
    void AddDeveloper(const web::http::http_request *request);
    void DeleteDeveloperById(const web::http::http_request *request);

protected:

private:
    Service _service;

    /** ERROR */
    void handle_error(pplx::task<void>& t);
};

#endif // CONTROLLER_HPP
