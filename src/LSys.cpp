#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "LSys.h"
#include "ProductionRule.h"

std::string LSys::getAxiom() const
{
    return m_axiom;
}

std::vector<ProductionRule> LSys::getPrules() const
{
    return m_Prules;
}

void LSys::setAxiom(const std::string & _axiom)
{
    m_axiom= _axiom;
}

void LSys::setPrules(const std::vector<ProductionRule> & _Prules)
{
    m_Prules= _Prules;
}


void LSys::addPrule(std::string _pre, std::string _key, std::string _post, std::string _def, float _weight)
{
    bool thereis_Prule = false;

    //add definition to existing production rule
    for(unsigned int i=0;i<m_Prules.size();++i)
    {
        if((m_Prules[i].m_key == _key) && (m_Prules[i].m_pre_condition == _pre) && (m_Prules[i].m_post_condition == _post))
        {
            m_Prules[i].m_definitions[_def]=_weight;
            m_Prules[i].m_definitions = definitionsNormalization(m_Prules[i].m_definitions);
            thereis_Prule = true;
            break;
        }
    }
    //add brand new production rule
    if( thereis_Prule==false)
    {
        ProductionRule Prule;
        Prule.m_pre_condition = _pre;
        Prule.m_post_condition = _post;
        Prule.m_key = _key;
        Prule.m_definitions[_def]= 1.0f;
        m_Prules.push_back(Prule);
    }
}


std::unordered_map<std::string, float> LSys::definitionsNormalization(std::unordered_map<std::string, float> defins)
{

    float sw=0.0f;


    //go through deinitions and sum

    for(auto iter=defins.begin(); iter != defins.end(); ++iter)
    {
        sw += iter->second;
    }

    //go through definitions and normalize
    for(auto iter=defins.begin(); iter != defins.end(); ++iter)
    {

        iter->second /= sw;
    }
    return defins;
}



void LSys::removePRuleonKey(std::string m_key)
{
    //go through Prules and if key is matched delete rule
    for(unsigned int i=0; i< m_Prules.size();++i)
    {
        if(m_Prules[i].m_key == m_key)
        {
            m_Prules.erase((m_Prules.begin()+i));
        }
    }
}


void LSys::rmPRuleDefinitiononKey(std::string m_key, std::string _def)
{

    for(unsigned int i=0; i<m_Prules.size(); ++i)
    {
        if(m_Prules[i].m_key==m_key)
        {
            for(auto iter=m_Prules[i].m_definitions.begin(); iter!=m_Prules[i].m_definitions.end();++iter)
            {
                if(iter->first==_def)
                {
                    m_Prules[i].m_definitions.erase(iter);
                }

            }
        }
    }
}

///@brief method to print on standard output
void LSys::print()
{

    //print parameters

    std::cout<<"L-Sys\n";

    std::cout<<"\nAxiom:\n"<<m_axiom<<'\n';
    std::cout<<"\nAngle:\n"<<m_angle<<'\n';
    std::cout<<"\nIterations\n"<<m_iterations<<'\n';
    std::cout<<"\nScale/drawLenght\n"<<m_scale<<'\n';
    std::cout<<"\nPrules:\n";


    for (unsigned int i=0; i<m_Prules.size();++i)
    {

        for(auto iter=m_Prules[i].m_definitions.begin(); iter!=m_Prules[i].m_definitions.end();++iter)
        {

            //print Prules
            if((m_Prules[i].m_pre_condition=="") && (m_Prules[i].m_post_condition==""))
            {
                std::cout<<m_Prules[i].m_key<<'('<< iter->second <<")  ->  " << iter->first<<'\n';
            }
            else if((m_Prules[i].m_pre_condition!="") && (m_Prules[i].m_post_condition==""))
            {
                std::cout<<m_Prules[i].m_pre_condition<<'<' << m_Prules[i].m_key <<'(' << iter->second<< ") -> "<<iter->first<<'\n';

            }
            else if((m_Prules[i].m_pre_condition=="")&&(m_Prules[i].m_post_condition!=""))
            {
                std::cout<< m_Prules[i].m_key <<'>'<< m_Prules[i].m_post_condition <<'(' << iter->second<<") -> "<<iter->first<<'\n';

            }
            else if((m_Prules[i].m_pre_condition!="")&&(m_Prules[i].m_post_condition!=""))
            {
                std::cout<<m_Prules[i].m_pre_condition<< '<' << m_Prules[i].m_key << '>' << m_Prules[i].m_post_condition << '('<< iter->second<<") ->"<<iter->first<<'\n';

            }
        }
    }

    std::cout<<'\n';
}

///@brief method to print to file
void LSys::Tofile(const char *_file_name)
{

    std::ofstream l_file;

    //save parameters to file

    l_file.open(_file_name);
    std::cout<<"aperto:\n";
    l_file << "axiom:" <<'\n';
    l_file << m_axiom << " ;"<<'\n';
    l_file << '\n';

    l_file << "angle:"<<'\n';
    l_file << m_angle << " ;\n";
    l_file << '\n';

    l_file << "iterations:"<<'\n';
    l_file << m_iterations << " ;"<<'\n';
    l_file << '\n';

    l_file << "scale:"<<'\n';
    l_file << m_scale <<" ;"<<'\n';
    l_file << '\n';

    l_file << "constants:"<<'\n';
    for(unsigned int i=0; i<m_constants.size(); ++i)
    {
        l_file << m_constants[i] << " ";

    }
    l_file << ";"<<'\n';
    l_file << '\n';
    //saving Prules
    l_file <<"Prules:"<<'\n';

    for(unsigned int i=0; i< m_Prules.size(); ++i)
    {
        for(auto iter=m_Prules[i].m_definitions.begin(); iter!=m_Prules[i].m_definitions.end(); ++iter)
        {
            if((m_Prules[i].m_pre_condition=="") && (m_Prules[i].m_post_condition==""))
            {
                l_file << m_Prules[i].m_key<<" ("<<iter->second<<") "<<iter->first<<" ;\n";
            }
            else if((m_Prules[i].m_pre_condition!="") && (m_Prules[i].m_post_condition==""))
            {
                l_file << m_Prules[i].m_pre_condition << "<" << m_Prules[i].m_key << " (" << iter->second << ") " << iter->first <<" ;\n";
            }
            else if((m_Prules[i].m_pre_condition=="") && (m_Prules[i].m_post_condition!=""))
            {
                l_file << m_Prules[i].m_key << ">" << m_Prules[i].m_post_condition << " (" << iter->second <<") " << iter->first<<" ;\n";
            }
            else if((m_Prules[i].m_pre_condition!="") && (m_Prules[i].m_post_condition!=""))
            {
                l_file << m_Prules[i].m_pre_condition << "<" << m_Prules[i].m_key << ">" << m_Prules[i].m_post_condition << " (" << iter->second << ") " << iter->first <<" ;\n";

            }
        }
    }
l_file << '\n';
l_file.close();

}
