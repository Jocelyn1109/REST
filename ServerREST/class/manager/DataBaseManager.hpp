/**
* Manager for the Postgres data base.
* @author: Jocelyn GIROD
* @date: Septembre 2023
*/

#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <string>
#include <pqxx/pqxx>

class DataBaseManager {
public:

    // Singleton not cloneable
    DataBaseManager(DataBaseManager &other) = delete;

    virtual ~DataBaseManager();

    // Singleton not assignable
    void operator=(const DataBaseManager &) = delete;

    static DataBaseManager * GetInstance(std::string *dataBaseParam);

    void Connect();
    void Disconnect();
    static pqxx::work *GetTransaction()
    {
        return DataBaseManager::_pTransaction;
    }

    static void DeleteInstance();

protected:


private:

    // Constructor
    DataBaseManager(std::string *dataBaseParam);

    static DataBaseManager *pDataBaseManager;
    static pqxx::work *_pTransaction;
    pqxx::connection *_pDbConnection;
};

#endif // DATABASEMANAGER_HPP
