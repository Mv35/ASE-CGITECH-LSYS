#include <iostream>
#include "LSysExtFactory.h"
#include "LSys0L.h"

std::unordered_map<std::string, LSysExtFactory::createCallB> LSysExtFactory::m_lsystem;

void LSysExtFactory::registerLSys(const std::string &type, createCallB cb)
{

   m_lsystem[type] =cb;
}

void LSysExtFactory::unregisterLSys(const std::string &type)
{
    m_lsystem.erase(type);
}
LSys* LSysExtFactory::generateLSys(const std::string &type, const LSysStruct &pa)
{
    //auto it
    std::unordered_map<std::string , createCallB>::iterator iter = m_lsystem.find(type);
    if( iter != m_lsystem.end())
    {
        return (iter->second)(pa);
    }
    return NULL;
}
