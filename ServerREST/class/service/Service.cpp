#include <iostream>
#include <vector>
#include "Service.hpp"
#include "data/entities/DataEntities.hpp"

using namespace std;

Service::Service()
{

}

Service::~Service()
{
    //dtor
}

/**
* GET developer by id
*/
DeveloperDto * Service::GetDeveloperById(int id)
{

    DeveloperEntity * developerEntity = _developerDao.GetDeveloperById(id);
    DeveloperDto * developerDto = new DeveloperDto();

    if(developerEntity!=nullptr) {
        developerDto->id = developerEntity->id;
        developerDto->first_name = developerEntity->first_name;
        developerDto->name = developerEntity->name;
        developerDto->age = developerEntity->age;
        developerDto->address = developerEntity->address;
        developerDto->country = developerEntity->country;
        developerDto->phone_number = developerEntity->phone_number;
        developerDto->company = developerEntity->company;
        developerDto->development_language = developerEntity->development_language;
    }

    delete developerEntity;
    return developerDto;
}

/**
* GET all developers
*/
DevelopersDto * Service::GetAllDevelopers()
{
    vector<DeveloperEntity> * developersEntity = _developerDao.GetAllDevelopers();
    DevelopersDto * developersDto = new DevelopersDto();

    if(developersEntity!=nullptr) {
        for(auto iter = developersEntity->begin(); iter!=developersEntity->end(); ++iter) {
            DeveloperDto dto;
            dto = DeveloperDto::DeveloperEntityToDto((*iter));
            developersDto->vDevelopersDto.push_back(dto);
        }
    }

    delete developersEntity;
    return developersDto;
}

/**
* POST add developer
*/
void Service::AddDeveloper(DeveloperDto developerDto)
{
    //TODO: adding developer in database
    cout << "Developer added" << endl;
}

/**
* DELETE developer
*/
void Service::DeleteDeveloperById(int id)
{
    //TODO: delete developer by id in database
    cout << "Developer with id: " << id << " has been deleted" << endl;
}
