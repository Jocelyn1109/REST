#include <string>
#include "DeveloperDao.hpp"

using namespace std;

DeveloperDao::DeveloperDao()
{
    _pTransaction = DataBaseManager::GetTransaction();
}

DeveloperDao::~DeveloperDao()
{
    //dtor
}

vector<DeveloperEntity> * DeveloperDao::GetAllDevelopers()
{
    vector<DeveloperEntity> * result = new vector<DeveloperEntity>;

    if(_pTransaction != nullptr) {
        utility::string_t sql_query("SELECT * FROM public.\"Developers\"");
        pqxx::result r = _pTransaction->exec(sql_query.c_str());

        for(pqxx::result::const_iterator c = r.begin(); c != r.end(); ++c) {
            DeveloperEntity entity;
            entity.id = c[0].as<int>();
            entity.first_name = c[1].as<string>();
            entity.name = c[2].as<string>();
            entity.age = c[3].as<int>();
            entity.address = c[4].as<string>();
            entity.country = c[5].as<string>();
            entity.phone_number = c[6].as<string>();
            entity.company = c[7].as<string>();
            entity.development_language = c[8].as<string>();
            result->push_back(entity);
        }
    }

    // ascending sort
    std::sort(result->begin(), result->end(), [](DeveloperEntity &a, DeveloperEntity &b) {
        return a.id < b.id;
    });

    return result;
}

DeveloperEntity * DeveloperDao::GetDeveloperById(int id)
{

    string id_str = std::to_string(id);
    utility::string_t sql_query("SELECT * FROM public.\"Developers\" WHERE id=\'");
    sql_query.append(id_str).append("\'");

    DeveloperEntity *entity = nullptr;

    pqxx::result r = _pTransaction->exec(sql_query.c_str());
    if(r.capacity()>0) {
        entity = new DeveloperEntity();
        entity->id = r[0]["id"].as<int>();
        entity->first_name = r[0]["first_name"].as<string>();
        entity->name = r[0]["name"].as<string>();
        entity->age = r[0]["age"].as<int>();
        entity->address = r[0]["address"].as<string>();
        entity->country = r[0]["country"].as<string>();
        entity->phone_number = r[0]["phone_number"].as<string>();
        entity->company = r[0]["company"].as<string>();
        entity->development_language = r[0]["development_language"].as<string>();
    }

    return entity;
}
