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

///@brief method to add production rule to class
void LSys::addPrule(std::string pre, std::string key, std::string post, std::string def, float chance)
{
    bool thereis_Prule = false;

    //add definition to existing production rule
    for(unsigned int i=0;i<m_Prules.size();++i)
    {
        if((m_Prules[i].key == key) && (m_Prules[i].pre_condition == pre) && (m_Prules[i].post_condition == post))
        {
            m_Prules[i].definitions[def]=chance;
            m_Prules[i].definitions = definitionsNormalization(m_Prules[i].definitions);
            thereis_Prule = true;
            break;
        }
    }
    //add brand new production rule
    if( thereis_Prule==false)
    {
        ProductionRule Prule;
        Prule.pre_condition = pre;
        Prule.post_condition = post;
        Prule.key = key;
        Prule.definitions[def]= 1.0f;
        m_Prules.push_back(Prule);
    }
}

///@brief method to set the sum of the float values of the map to 1
/// in order to calculate percentage for each definitions
std::unordered_map<std::string, float> LSys::definitionsNormalization(std::unordered_map<std::string, float> defins)
{

    float sw=0.0f;




    for(auto iter=defins.begin(); iter != defins.end(); ++iter)
    {
        sw += iter->second;
    }

    for(auto iter=defins.begin(); iter != defins.end(); ++iter)
    {

        iter->second /= sw;
    }
    return defins;
}


///@brief method to remove PRules according to passed key
void LSys::removePRuleonKey(std::string key)
{
    for(unsigned int i=0; i< m_Prules.size();++i)
    {
        if(m_Prules[i].key == key)
        {
            m_Prules.erase((m_Prules.begin()+i));
        }
    }
}

///@brief method to remove Prule's definition according to key and def
void LSys::rmPRuleDefinitiononKey(std::string key, std::string def)
{

    for(unsigned int i=0; i<m_Prules.size(); ++i)
    {
        if(m_Prules[i].key==key)
        {
            for(auto iter=m_Prules[i].definitions.begin(); iter!=m_Prules[i].definitions.end();++iter)
            {
                if(iter->first==def)
                {
                    m_Prules[i].definitions.erase(iter);
                }

            }
        }
    }
}

///@brief method to print on standard output
void LSys::print()
{



    std::cout<<"L-Sys\n";

    std::cout<<"\nAxiom:\n"<<m_axiom<<'\n';
    std::cout<<"\nAngle:\n"<<m_angle<<'\n';
    std::cout<<"\nIterations\n"<<m_iterations<<'\n';
    std::cout<<"\nScale/drawLenght\n"<<m_scale<<'\n';
    std::cout<<"\nPrules:\n";
    for (unsigned int i=0; i<m_Prules.size();++i)
    {
        //std::cout<<i<<"1for\n";
        for(auto iter=m_Prules[i].definitions.begin(); iter!=m_Prules[i].definitions.end();++iter)
        {
            //std::cout<<iter->first<<"2for\n";
            if((m_Prules[i].pre_condition=="") && (m_Prules[i].post_condition==""))
            {
                std::cout<<m_Prules[i].key<<'('<< iter->second <<")  ->  " << iter->first<<'\n';
            }
            else if((m_Prules[i].pre_condition!="") && (m_Prules[i].post_condition==""))
            {
                std::cout<<m_Prules[i].pre_condition<<'<' << m_Prules[i].key <<'(' << iter->second<< ") -> "<<iter->first<<'\n';

            }
            else if((m_Prules[i].pre_condition=="")&&(m_Prules[i].post_condition!=""))
            {
                std::cout<< m_Prules[i].key <<""<< m_Prules[i].post_condition <<'(' << iter->second<<") -> "<<iter->first<<'\n';

            }
            else if((m_Prules[i].pre_condition!="")&&(m_Prules[i].post_condition!=""))
            {
                std::cout<<m_Prules[i].pre_condition<< '<' << m_Prules[i].key << '>' << m_Prules[i].post_condition << '('<< iter->second<<") ->"<<iter->first<<'\n';

            }
        }
    }

    std::cout<<'\n';
}

///@brief method to print to file
void LSys::Tofile(const char *file_name)
{

    std::ofstream l_file;

    std::cout<<"tofile chiamata\n";

    l_file.open(file_name);
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

    l_file <<"Prules:"<<'\n';

    for(unsigned int i=0; i< m_Prules.size(); ++i)
    {
        for(auto iter=m_Prules[i].definitions.begin(); iter!=m_Prules[i].definitions.end(); ++iter)
        {
            if((m_Prules[i].pre_condition=="") && (m_Prules[i].post_condition==""))
            {
                l_file << m_Prules[i].key<<" ("<<iter->second<<") "<<iter->first<<" ;\n";
            }
            else if((m_Prules[i].pre_condition!="") && (m_Prules[i].post_condition==""))
            {
                l_file << m_Prules[i].pre_condition << "<" << m_Prules[i].key << " (" << iter->second << ") " << iter->first <<" ;\n";
            }
            else if((m_Prules[i].pre_condition=="") && (m_Prules[i].post_condition!=""))
            {
                l_file << m_Prules[i].key << ">" << m_Prules[i].post_condition << " (" << iter->second <<") " << iter->first<<" ;\n";
            }
            else if((m_Prules[i].pre_condition!="") && (m_Prules[i].post_condition!=""))
            {
                l_file << m_Prules[i].pre_condition << "<" << m_Prules[i].key << ">" << m_Prules[i].post_condition << " (" << iter->second << ") " << iter->first <<" ;\n";

            }
        }
    }
l_file << '\n';
l_file.close();

}
