/**
* Utility for request.
* @author: Jocelyn GIROD
* @date: Septembre 2023
*/

#ifndef REQUESTUTIL_HPP
#define REQUESTUTIL_HPP

#include "Common.hpp"


class RequestUtil {
public:
    RequestUtil();
    virtual ~RequestUtil();

    static utility::string_t GetDataInQuery(const web::http::http_request *request, const utility::string_t data);
    static void DisplaySplitedRequestPath(const web::http::http_request *request);

protected:

private:
};

#endif // REQUESTUTIL_HPP
