/**
* Handler for request GET, PUT, POST, DELETE.
* @author: Jocelyn GIROD
* @date: Septembre 2023
*/

#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "Common.hpp"
#include "Controller.hpp"

class Handler {
public:
    Handler();
    Handler(utility::string_t url);
    virtual ~Handler();

    //method
    pplx::task<void>open()
    {
        return m_listener.open();
    }
    pplx::task<void>close()
    {
        return m_listener.close();
    }

protected:

private:

    /** Handler for GET request */
    void handle_get(web::http::http_request request);
    /** Handler for PUT request */
    void handle_put(web::http::http_request request);
    /** Handler for POST request */
    void handle_post(web::http::http_request request);
    /** Handler for DELETE request */
    void handle_delete(web::http::http_request request);

    /** Handler for error */
    void handle_error(pplx::task<void>& t);

    web::http::experimental::listener::http_listener m_listener;

    Controller _controller;
};

#endif // HANDLER_HPP
