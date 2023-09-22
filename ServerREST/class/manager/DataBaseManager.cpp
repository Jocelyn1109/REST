#include <iostream>
#include "DataBaseManager.hpp"

using namespace std;

DataBaseManager * DataBaseManager::pDataBaseManager = nullptr;
pqxx::work * DataBaseManager::_pTransaction = nullptr;


DataBaseManager::DataBaseManager(std::string *dataBaseParam)
{
    _pDbConnection = new pqxx::connection(*dataBaseParam);

    if(_pDbConnection != nullptr && _pDbConnection->is_open()) {
        cout << "Open database " << dataBaseParam << " successfully" << endl;
    }
    else {
        cout << "Can't open database" << endl;
    }

    _pTransaction = new pqxx::work(*_pDbConnection);

}

DataBaseManager::~DataBaseManager()
{
    _pDbConnection->disconnect();
    delete _pDbConnection;
    _pDbConnection = nullptr;
}

DataBaseManager *DataBaseManager::GetInstance(std::string *dataBaseParam)
{
    if(DataBaseManager::pDataBaseManager == nullptr) {
        pDataBaseManager = new DataBaseManager(dataBaseParam);
    }

    return DataBaseManager::pDataBaseManager;
}

void DataBaseManager::DeleteInstance()
{
    delete _pTransaction;
    delete pDataBaseManager;
    _pTransaction = nullptr;
    pDataBaseManager = nullptr;
}
