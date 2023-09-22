#ifndef DATAENTITIES_HPP_INCLUDED
#define DATAENTITIES_HPP_INCLUDED

#include <cpprest/json.h>

struct DeveloperEntity {
    int id;
    utility::string_t first_name;
    utility::string_t name;
    int age;
    utility::string_t address;
    utility::string_t country;
    utility::string_t phone_number;
    utility::string_t company;
    utility::string_t development_language;
};


#endif // DATAENTITIES_HPP_INCLUDED
