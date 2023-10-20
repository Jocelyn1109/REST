#ifndef DATA_HPP_INCLUDED
#define DATA_HPP_INCLUDED

#include <cpprest/json.h>
#include <vector>

struct People {
    int id;
    utility::string_t firstname;
    utility::string_t name;
    int age;
    utility::string_t address;
    utility::string_t country;
    utility::string_t development_language;

    //json to People
    static People FromJson(const web::json::object &json_object)
    {
        People people;
        if(!json_object.at(U("id")).as_string().empty()) {
            people.id = json_object.at(U("id")).as_integer();
        }
        people.firstname = json_object.at(U("firstname")).as_string();
        people.name = json_object.at(U("name")).as_string();
        people.age = json_object.at(U("age")).as_integer();
        people.address = json_object.at(U("address")).as_string();
        people.country = json_object.at(U("country")).as_string();
        people.development_language = json_object.at(U("development_language")).as_string();
        return people;
    }

    web::json::value AsJSON() const
    {
        web::json::value result = web::json::value::object();
        result[U("id")] = web::json::value::number(id);
        result[U("firstname")] = web::json::value::string(firstname);
        result[U("name")] = web::json::value::string(name);
        result[U("age")] = web::json::value::number(age);
        result[U("address")] = web::json::value::string(address);
        result[U("country")] = web::json::value::string(country);
        result[U("development_language")] = web::json::value::string(development_language);
        return result;
    }
};

struct DataPeople {

    std::vector<People> peoples;
    utility::string_t job;

    DataPeople() {}

    void Clear()
    {
        peoples.clear();
    }

    static DataPeople FromJSON(const web::json::object &json_object)
    {
        DataPeople dataPeople;

        web::json::value job = json_object.at(U("job"));
        dataPeople.job = job.as_string();

        web::json::value p = json_object.at(U("people"));
        for(auto iter = p.as_array().begin(); iter!=p.as_array().end(); ++iter) {
            if(!iter->is_null()) {
                People people;
                people = People::FromJson(iter->as_object());
                dataPeople.peoples.push_back(people);
            }
        }

        return dataPeople;
    }

    web::json::value AsJSON() const
    {

        web::json::value res = web::json::value::object();
        res[U("job")] = web::json::value::string(job);

        web::json::value jPeoples = web::json::value::array(peoples.size());

        int index = 0;
        for(auto iter = peoples.begin(); iter!=peoples.end(); iter++) {
            jPeoples[index++] = iter->AsJSON();
        }

        res[U("people")] = jPeoples;
        return res;
    }
};


#endif // DATA_HPP_INCLUDED
