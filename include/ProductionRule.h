#ifndef PRODUCTIONRULE_H_
#define PRODUCTIONRULE_H_


///@file ProductionRule.h
///@brief The ProductionRule data struct
///the production rule data structure is composed of an unordered_map of definitions
/// and corresponding float value, a key string and the pre and post conditions string that will be used for
/// context sensitive l-systems

struct ProductionRule
{
 //----------------------------------------------------------------------------------------------------------------------
 ///@brief post condition of the key
 /// for context sensitive L-systems  A<B a before b
 //----------------------------------------------------------------------------------------------------------------------
 std::string m_post_condition;
 //----------------------------------------------------------------------------------------------------------------------
 ///@brief pre condition of the key B>A a after b
 /// for context sensitive L-systems
 //----------------------------------------------------------------------------------------------------------------------
 std::string m_pre_condition;
 //----------------------------------------------------------------------------------------------------------------------
 ///@brief the current evaluated character also known as key
 //----------------------------------------------------------------------------------------------------------------------
 std::string m_key;
 //----------------------------------------------------------------------------------------------------------------------
 ///@brief definitions for the key and both conditions.
 /// if conditions exist a non-deterministic system must be implemented
 //----------------------------------------------------------------------------------------------------------------------
 std::unordered_map<std::string, float> m_definitions;

};

#endif // PRODUCTIONRULE_H_
