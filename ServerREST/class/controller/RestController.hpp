/**
* Generic class for controler
* @author: Jocelyn GIROD
* @date: Septembre 2023
*/
#ifndef RESTCONTROLLER_HPP
#define RESTCONTROLLER_HPP

#include "Common.hpp"

class RestController
{
    public:
        RestController();
        virtual ~RestController();

    protected:

    /** GET */
    virtual void handle_get(web::http::http_request request);
    /** PUT */
    virtual void handle_put(web::http::http_request request);
    /** POST */
    virtual void handle_post(web::http::http_request request);
    /** DELETE */
    virtual void handle_delete(web::http::http_request request);

    /** ERROR */
    void handle_error(pplx::task<void>& t);

    private:
};

#endif // RESTCONTROLLER_HPP
