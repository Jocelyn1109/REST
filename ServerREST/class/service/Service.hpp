/**
* Service.
* @author: Jocelyn GIROD
* @date: Septembre 2023
*/

#ifndef SERVICE_HPP
#define SERVICE_HPP

#include "data/dto/DeveloperDto.hpp"
#include "DeveloperDao.hpp"


class Service {
public:
    Service();
    virtual ~Service();

    DevelopersDto * GetAllDevelopers();
    DeveloperDto * GetDeveloperById(int id);
    void AddDeveloper(DeveloperDto developerDto);
    void UpdateDeveloper(DeveloperDto developerDto);
    void DeleteDeveloperById(int id);

protected:

private:
    DeveloperDao _developerDao;
};

#endif // SERVICE_HPP
