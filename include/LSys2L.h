#ifndef LSYS2L_H
#define LSYS2L_H


#include "LSys.h"

#include "LSys0L.h"


///@file LSys2L.h
/// @brief L-system class of type 2L  derived from LSys.h
/// used to generate stochastic 2 side sensitive l-systems

class LSys2L : public LSys0L
{
public:
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief constructor of the LSys1L class
    /// @param reference to LSysStruct instance
    //----------------------------------------------------------------------------------------------------------------------
    LSys2L (const LSysStruct&);
    //~LSys2L();
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief Pure Virtual Method to develop a stochastic 1 side context sensitive L-system
    /// @param iterations number of iterations to perform
    /// @param out_results vector of strings to contain the L-System's results
    /// @param flag to indicate that all iterations must be developed and stored
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<std::string> develop(int _iterations, std::vector<std::string> &_out_results, bool _all_stages);

    //----------------------------------------------------------------------------------------------------------------------
    ///@brief to generate an instance of the LSys2L class through factory
    //----------------------------------------------------------------------------------------------------------------------
    static LSys *generate(const LSysStruct &_p) {return new LSys2L(_p);}
};


#endif // LSYS2L_H
