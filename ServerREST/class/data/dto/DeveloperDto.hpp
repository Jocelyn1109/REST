#ifndef DEVELOPERDTO_HPP_INCLUDED
#define DEVELOPERDTO_HPP_INCLUDED

#include <cpprest/json.h>
#include "data/entities/DataEntities.hpp"

struct DeveloperDto {
    int id;
    utility::string_t first_name;
    utility::string_t name;
    int age;
    utility::string_t address;
    utility::string_t country;
    utility::string_t phone_number;
    utility::string_t company;
    utility::string_t development_language;

    //Json to Developer DTO
    static DeveloperDto FromJson(const web::json::object &json_object)
    {
        DeveloperDto developerDto;
        if(!json_object.at(U("id")).as_string().empty()) {
            developerDto.id = json_object.at(U("id")).as_integer();
        }
        developerDto.first_name = json_object.at(U("firstname")).as_string();
        developerDto.name = json_object.at(U("name")).as_string();
        developerDto.age = json_object.at(U("age")).as_integer();
        developerDto.address = json_object.at(U("address")).as_string();
        developerDto.country = json_object.at(U("country")).as_string();
        developerDto.phone_number = json_object.at(U("phone_number")).as_string();
        developerDto.company = json_object.at(U("company")).as_string();
        developerDto.development_language = json_object.at(U("development_language")).as_string();
        return developerDto;
    }

    // Developer DTO to Json
    web::json::value AsJSON() const
    {
        web::json::value result = web::json::value::object();
        result[U("id")] = web::json::value::number(id);
        result[U("first_name")] = web::json::value::string(first_name);
        result[U("name")] = web::json::value::string(name);
        result[U("age")] = web::json::value::number(age);
        result[U("address")] = web::json::value::string(address);
        result[U("country")] = web::json::value::string(country);
        result[U("phone_number")] = web::json::value::string(phone_number);
        result[U("company")] = web::json::value::string(company);
        result[U("development_language")] = web::json::value::string(development_language);
        return result;
    }

    // Convert DeveloperEntity to DeveloperDto
    static DeveloperDto DeveloperEntityToDto(DeveloperEntity &entity)
    {
        DeveloperDto developerDto;
        developerDto.id = entity.id;
        developerDto.first_name = entity.first_name;
        developerDto.name = entity.name;
        developerDto.age = entity.age;
        developerDto.address = entity.address;
        developerDto.country = entity.country;
        developerDto.phone_number = entity.phone_number;
        developerDto.company = entity.company;
        developerDto.development_language = entity.development_language;

        return developerDto;
    }
};

struct DevelopersDto {
    std::vector<DeveloperDto> vDevelopersDto;
    utility::string_t dev;

    void Clear()
    {
        vDevelopersDto.clear();
    }

    // Json to Developers Dto
    static DevelopersDto FromJSON(const web::json::object &json_object)
    {
        DevelopersDto developersDto;
        web::json::value dev_json = json_object.at(U("developers"));
        developersDto.dev = dev_json.as_string();

        web::json::value p = json_object.at(U("developer"));
        for(auto iter = p.as_array().begin(); iter!=p.as_array().end(); ++iter) {
            if(!iter->is_null()) {
                DeveloperDto developerDto;
                developerDto = DeveloperDto::FromJson(iter->as_object());
                developersDto.vDevelopersDto.push_back(developerDto);
            }
        }

        return developersDto;
    }

    // DevelopersDto to Json
    web::json::value AsJSON() const
    {
        web::json::value res = web::json::value::object();
        res[U("developers")] = web::json::value::string(dev);

        web::json::value json_developers = web::json::value::array(vDevelopersDto.size());

        int index = 0;
        for(auto iter = vDevelopersDto.begin(); iter!=vDevelopersDto.end(); iter++) {
            json_developers[index++] = iter->AsJSON();
        }

        res[U("developers")] = json_developers;
        return res;
    }
};


#endif // DEVELOPERDTO_HPP_INCLUDED
