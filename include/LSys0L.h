 #ifndef LSYS0L_H_
#define LSYS0L_H_

#include "LSys.h"
#include <iostream>

///@file LSys0L.h
/// @brief L-system class of type 0L  derived from LSys.h
/// used to generate stochastic non-context sensitive l-systems
///
class LSys0L : public LSys
{
public:
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief constructor and deconstructor

    LSys0L(const LSysStruct &);

    ~LSys0L();
    //----------------------------------------------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------------------------------------------
    ///@brief method required for the initialization of a Stochatic l-system type
    /// will be called only if there is more than 1 definition for alphabet's symbol
    //----------------------------------------------------------------------------------------------------------------------
    std::string for0Lgen(const std::unordered_map<std::string, float> & _defins);



    //----------------------------------------------------------------------------------------------------------------------
    ///@brief Pure Virtual Method to develop a stochastic non-context sensitive L-system
    /// @param iterations number of iterations to perform
    /// @param out_results vector of strings to contain the L-System's results
    /// @param flag to indicate that all iterations must be developed and stored
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<std::string> develop(int _iterations, std::vector<std::string> &_out_results, bool _all_stages);

    //----------------------------------------------------------------------------------------------------------------------
    ///@brief to generate an instance of the LSys0L class through factory
    //----------------------------------------------------------------------------------------------------------------------
    static LSys *generate(const LSysStruct &_p) {return new LSys0L(_p);}

};

#endif // LSYS0L_H_
