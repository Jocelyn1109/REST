/**
* Dao for developers.
* @author: Jocelyn GIROD
* @date: Septembre 2023
*/

#ifndef DEVELOPERDAO_HPP
#define DEVELOPERDAO_HPP

#include <vector>
#include "DataBaseManager.hpp"
#include "data/entities/DataEntities.hpp"

class DeveloperDao {
public:
    DeveloperDao();
    virtual ~DeveloperDao();

    std::vector<DeveloperEntity> * GetAllDevelopers();
    DeveloperEntity * GetDeveloperById(int id);

protected:

private:
    pqxx::work *_pTransaction;
};

#endif // DEVELOPERDAO_HPP
