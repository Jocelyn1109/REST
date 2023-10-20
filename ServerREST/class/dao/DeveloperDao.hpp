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
#include "data/dto/DeveloperDto.hpp"

class DeveloperDao {
public:
    DeveloperDao();
    virtual ~DeveloperDao();

    /**
    * Get all developers.
    * @return a vector containing all developers as entity.
    */
    std::vector<DeveloperEntity> * GetAllDevelopers();

    /**
    * Get developer by id.
    * @param the developer id.
    * @return the result as entity.
    */
    DeveloperEntity * GetDeveloperById(int id);

    /**
    * Adding a new developer.
    * @param the new developer as dto.
    */
    void AddNewDeveloper(const DeveloperDto &developer);

    /**
    * Update developer.
    * @param the developer to update.
    */
    void UpdateDeveloper(const DeveloperDto &developer);

    /**
    * Delete developer by id.
    * @param the developer id.
    */
    void DeleteDeveloper(int id);

protected:

private:
    pqxx::work *_pTransaction;
};

#endif // DEVELOPERDAO_HPP
