#ifndef DATA_HPP_INCLUDED
#define DATA_HPP_INCLUDED

#include <cpprest/json.h>
#include <vector>

struct People {
    utility::string_t name;
    int age;

    //json to People
    static People FromJson(const web::json::object &json_object)
    {
        People people;
        people.name = json_object.at(U("name")).as_string();
        people.age = json_object.at(U("age")).as_integer();
        return people;
    }

    web::json::value AsJSON() const
    {
        web::json::value result = web::json::value::object();
        result[U("name")] = web::json::value::string(name);
        result[U("age")] = web::json::value::number(age);
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
