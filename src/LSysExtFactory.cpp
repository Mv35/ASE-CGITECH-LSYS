#include <iostream>
#include "LSysExtFactory.h"
#include "LSys0L.h"
#include "LSys1L.h"

//----------------------------------------------------------------------------------------------------------------------

std::unordered_map<std::string, LSysExtFactory::createCallB> LSysExtFactory::m_lsystem;

//----------------------------------------------------------------------------------------------------------------------

void LSysExtFactory::registerLSys(const std::string &_type, createCallB _cb)
{

   m_lsystem[_type] =_cb;
}

//----------------------------------------------------------------------------------------------------------------------

void LSysExtFactory::unregisterLSys(const std::string &type)
{
    m_lsystem.erase(type);
}

//----------------------------------------------------------------------------------------------------------------------

LSys* LSysExtFactory::generateLSys(const std::string &type, const LSysStruct &_pa)
{

    std::unordered_map<std::string , createCallB>::iterator iter = m_lsystem.find(type);
    if( iter != m_lsystem.end())
    {
        return (iter->second)(_pa);
    }
    return NULL;
}
//----------------------------------------------------------------------------------------------------------------------
