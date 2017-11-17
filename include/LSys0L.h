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

    ///@brief constructor and deconstructor

    LSys0L(const LSysStruct &);

    ~LSys0L();

    ///@brief method required for the initialization of a Stochatic l-system type
    /// will be called only if there is more than 1 definition for alphabet's symbol

    std::string for0Lgen(const std::unordered_map<std::string, float> & defins);


    ///@brief method used to apply the production rules for a number of iterations and store the final iteration into
    /// a vector of strings so that every iteration can be accessed

    std::vector<std::string> develop(int iterations, std::vector<std::string> &out_results, bool all_stages);
    static LSys *generate(const LSysStruct &p) {return new LSys0L(p);}
    //static std::unique_ptr <LSys> generate (const LSysStruct &p) {return new LSys0L(p);}
};

#endif // LSYS0L_H_
