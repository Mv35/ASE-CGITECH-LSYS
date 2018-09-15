#ifndef LSYS1L_H
#define LSYS1L_H

#include "LSys.h"

#include "LSys0L.h"

///@file LSys1L.h
/// @brief L-system class of type 1L  derived from LSys.h
/// used to generate stochastic 1 side sensitive l-systems

class LSys1L : public LSys0L
{
public:
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief constructor of the LSys1L class
    /// @param reference to LSysStruct instance
    //----------------------------------------------------------------------------------------------------------------------
    LSys1L (const LSysStruct&);

    //~LSys1L();

    //----------------------------------------------------------------------------------------------------------------------
    ///@brief Pure Virtual Method to develop a stochastic 1 side context sensitive L-system
    /// @param iterations number of iterations to perform
    /// @param out_results vector of strings to contain the L-System's results
    /// @param flag to indicate that all iterations must be developed and stored
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<std::string> develop(int _iterations, std::vector<std::string> &_out_results, bool _all_stages);

    //----------------------------------------------------------------------------------------------------------------------
    ///@brief to generate an instance of the LSys1L class through factory
    //----------------------------------------------------------------------------------------------------------------------
    static LSys *generate(const LSysStruct &_p) {return new LSys1L(_p);}
};

#endif // LSYS1L_H
