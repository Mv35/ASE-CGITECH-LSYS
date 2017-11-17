#ifndef LSYSEXTFACTORY_H_
#define LSYSEXTFACTORY_H_

#include <string>
#include <map>
#include <unordered_map>
#include "LSys.h"

///@file LSysExtFactory.h
/// @brief L-system extendable factory class
/// used to handle the instantiation of the various LSys classes
/// Modified from :
/// Martin Reddy (5 Oct 2017) Chapter 3 of "Api Design for C++", Extendable Factory Pattern.

class LSysExtFactory
{
public:
    typedef LSys *(*createCallB)(const LSysStruct &p);

    static void registerLSys(const std::string &type, createCallB cb);

    static void unregisterLSys(const std::string &type);

    static LSys *generateLSys(const std::string &type, const LSysStruct &pa);

private:
    static std::unordered_map<std::string, createCallB> m_lsystem;
};


#endif //LSYSEXTFACTORY_H_
