#include <string>
#include <exception>
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

    try {
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
    }
    catch(pqxx::sql_error const &ex) {
        cerr << "SQL error: " << ex.what() << endl;
        cerr << "Query sql: " << ex.query() << endl;
        throw ex;
    }
    catch(exception const &ex) {
        throw ex;
    }

    return result;
}

DeveloperEntity * DeveloperDao::GetDeveloperById(int id)
{
    string id_str = std::to_string(id);
    utility::string_t sql_query("SELECT * FROM public.\"Developers\" WHERE id=\'");
    sql_query.append(id_str).append("\'");

    DeveloperEntity *entity = nullptr;

    try {
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
    }
    catch(pqxx::sql_error const &ex) {
        cerr << "SQL error: " << ex.what() << endl;
        cerr << "Query sql: " << ex.query() << endl;
        throw ex;
    }
    catch(exception const &ex) {
        throw ex;
    }

    return entity;
}

void DeveloperDao::AddNewDeveloper(const DeveloperDto &developer)
{
    utility::string_t sql_query("INSERT INTO public.\"Developers\" (first_name, name, age, address, country, phone_number, company, development_language) VALUES (");
    sql_query.append("\'").append(developer.first_name).append("\', ");
    sql_query.append("\'").append(developer.name).append("\', ");
    sql_query.append(std::to_string(developer.age)).append(", ");
    sql_query.append("\'").append(developer.address).append("\', ");
    sql_query.append("\'").append(developer.country).append("\', ");
    sql_query.append("\'").append(developer.phone_number).append("\', ");
    sql_query.append("\'").append(developer.company).append("\', ");
    sql_query.append("\'").append(developer.development_language).append("\')");

    cout << "Add new developer query: " << sql_query << endl;

    try {
        _pTransaction->exec(sql_query.c_str());
        _pTransaction->commit();
    }
    catch(pqxx::sql_error const &ex) {
        cerr << "SQL error: " << ex.what() << endl;
        cerr << "Query sql: " << ex.query() << endl;
        throw ex;
    }
    catch(exception const &ex) {
        throw ex;
    }
}

void DeveloperDao::UpdateDeveloper(const DeveloperDto &developer)
{
    utility::string_t sql_query("UPDATE public.\"Developers\" SET first_name=");
    sql_query.append("\'").append(developer.first_name).append("\', name=");
    sql_query.append("\'").append(developer.name).append("\', age=");
    sql_query.append("\'").append(std::to_string(developer.age)).append("\', address=");
    sql_query.append("\'").append(developer.address).append("\', country=");
    sql_query.append("\'").append(developer.country).append("\', phone_number=");
    sql_query.append("\'").append(developer.phone_number).append("\', company=");
    sql_query.append("\'").append(developer.company).append("\', development_language=");
    sql_query.append("\'").append(developer.development_language).append("\' WHERE id=");
    sql_query.append("\'").append(std::to_string(developer.id)).append("\'");

    cout << "Update developer query: " << sql_query << endl;

    try {
        _pTransaction->exec(sql_query.c_str());
        _pTransaction->commit();
    }
    catch(pqxx::sql_error const &ex) {
        cerr << "SQL error: " << ex.what() << endl;
        cerr << "Query sql: " << ex.query() << endl;
        throw ex;
    }
    catch(exception const &ex) {
        throw ex;
    }
}

void DeveloperDao::DeleteDeveloper(int id)
{
    string id_str = std::to_string(id);
    utility::string_t sql_query("DELETE FROM public.\"Developers\" WHERE id=\'");
    sql_query.append(id_str).append("\'");

    try {
        _pTransaction->exec(sql_query.c_str());
        _pTransaction->commit();
    }
    catch(pqxx::sql_error const &ex) {
        cerr << "SQL error: " << ex.what() << endl;
        cerr << "Query sql: " << ex.query() << endl;
        throw ex;
    }
    catch(exception const &ex) {
        throw ex;
    }
}
