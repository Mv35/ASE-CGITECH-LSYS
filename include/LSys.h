#ifndef LSYS_H_
#define LSYS_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include "LSysStruct.h"
#include "ProductionRule.h"


///@file LSys.h
///@brief L-system abstract class
///to be inherited by the rest of L-systems only 0L at the moment
/// it holds no direct constructor and holds a pure virtual abstract method "develop"
///  which will be inherited by the sub L-System classes.

class LSys
{
protected:
    ///@brief axiom
    std::string m_axiom;


    int m_angle;

    ///@brief iterations
    int m_iterations;

    ///@brief scale
    double m_scale;

    ///@brief vector of constants
    std::vector<std::string> m_constants;

    ///@brief Production rules vector
    std::vector<ProductionRule> m_Prules;


public:
    virtual ~LSys(){}

    /// Accessors methods

    std::string getAxiom() const;
    std::vector<ProductionRule> getPrules() const;

    /// Mutators methods
    void setAxiom(const std::string &);
    void setPrules(const std::vector<ProductionRule> &);

    ///@brief method add Production rule to the class
    void addPrule(std::string pre, std::string key, std::string post, std::string def, float weight);

    ///@brief method to normalize the definitions float values so that their sum is = to 1
    std::unordered_map<std::string, float> definitionsNormalization(std::unordered_map<std::string, float> def);

    ///@brief method to remove a Prule from passed key
    void removePRuleonKey(std::string key);
    ///@brief method to remove a definition
    void rmPRuleDefinitiononKey(std::string key, std::string def);
    ///@brief method to print the values of the class's members
    void print();
    ///@brief method to print to file the values of the class's members
    void Tofile(const char* file_name);


    /// Pure Virtual Method to be inherited from L-sys classes
    virtual std::vector<std::string> develop (int iterations, std::vector<std::string>& out_results, bool all_stages) = 0;

};

#endif //LSYS_H_
