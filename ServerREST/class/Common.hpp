#ifndef COMMON_HPP_INCLUDED
#define COMMON_HPP_INCLUDED

#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

#include <sys/time.h>

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include "cpprest/json.h"
#include "cpprest/filestream.h"
#include "cpprest/containerstream.h"
#include "cpprest/producerconsumerstream.h"

#include <locale>
#include <ctime>

struct Http_Request_Error {

    int http_error_code;
    utility::string_t errorMessage;

    web::json::value AsJSON() const
    {
        web::json::value json_value = web::json::value::object();
        json_value[U("code")] = web::json::value::number(http_error_code);
        json_value[U("message")] = web::json::value::string(errorMessage);
        return json_value;
    }

};


#endif // COMMON_HPP_INCLUDED
