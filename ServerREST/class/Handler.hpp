/**
* Handler gérant les requêtes GET, PUT, POST, DELETE
* TODO: UPDATE.
*/

#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "Common.hpp"

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

    /** GET */
    void handle_get(web::http::http_request message);
    /** PUT */
    void handle_put(web::http::http_request message);
    /** POST */
    void handle_post(web::http::http_request message);
    /** DELETE */
    void handle_delete(web::http::http_request message);

    /** ERROR */
    void handle_error(pplx::task<void>& t);

    web::http::experimental::listener::http_listener m_listener;
};

#endif // HANDLER_HPP
