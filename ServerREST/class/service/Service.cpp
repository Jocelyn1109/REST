#include <iostream>
#include <vector>
#include <exception>
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
    DeveloperDto * developerDto = new DeveloperDto();

    try {
        DeveloperEntity * developerEntity = _developerDao.GetDeveloperById(id);
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
            delete developerEntity;
        }
    }
    catch(exception const &ex) {
        throw ex;
    }

    return developerDto;
}

/**
* GET all developers
*/
DevelopersDto * Service::GetAllDevelopers()
{
    DevelopersDto * developersDto = new DevelopersDto();
    try {
        vector<DeveloperEntity> * developersEntity = _developerDao.GetAllDevelopers();
        if(developersEntity!=nullptr) {
            for(auto iter = developersEntity->begin(); iter!=developersEntity->end(); ++iter) {
                DeveloperDto dto;
                dto = DeveloperDto::DeveloperEntityToDto((*iter));
                developersDto->vDevelopersDto.push_back(dto);
            }
            delete developersEntity;
        }
    }
    catch(exception const &ex) {
        throw ex;
    }

    return developersDto;
}

/**
* POST add developer
*/
void Service::AddDeveloper(DeveloperDto developerDto)
{
    try {
        _developerDao.AddNewDeveloper(developerDto);
        cout << "Developer added" << endl;
    }
    catch(exception const &ex) {
        throw ex;
    }

}

/**
* UPDATE update developer
*/
void Service::UpdateDeveloper(DeveloperDto developerDto)
{
    try {
        _developerDao.UpdateDeveloper(developerDto);
        cout << "Developer updated" << endl;
    }
    catch(exception const &ex) {
        throw ex;
    }
}

/**
* DELETE developer
*/
void Service::DeleteDeveloperById(int id)
{
    try {
        _developerDao.DeleteDeveloper(id);
        cout << "Developer with id: " << id << " has been deleted" << endl;
    }
    catch(exception const &ex) {
        throw ex;
    }
}
