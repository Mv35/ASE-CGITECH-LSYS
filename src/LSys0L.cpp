#include "LSys0L.h"
#include "LSys.h"
#include <iostream>
#include <stdlib.h>
//----------------------------------------------------------------------------------------------------------------------
//constructor
LSys0L::LSys0L(const LSysStruct & s)
{
    m_axiom= s.m_axiom;
    m_angle= s.m_angle;
    m_scale= s.m_drawLenght;
    m_iterations= s.m_iteration;
    m_constants= s.m_constants;
    m_Prules= s.m_Prules;
}
//----------------------------------------------------------------------------------------------------------------------
//deconstructor

LSys0L::~LSys0L(){std::cout << "deconstructor called\n";}


//----------------------------------------------------------------------------------------------------------------------
//method for the stochastic choice of definitions
std::string LSys0L::for0Lgen(const std::unordered_map<std::string, float> &_defins)
{
    std::string Definitions; //definitions

    float r = (float)(rand()%100) / 100; //randomness

    //chose randomly between defins
    for(auto iter = _defins.begin(); iter != _defins.end(); ++iter)
    {
        if( r < iter->second)
        {

            Definitions = iter->first;
            break;
        }
        r-= iter->second;
    }

    return Definitions;


}


//----------------------------------------------------------------------------------------------------------------------
//actual method that develops a non context-sensitive Stochastic LSystem , can also generate Deterministic ones

std::vector<std::string> LSys0L::develop(int _iterations, std::vector<std::string> &_out_results, bool _all_stages)
{
    if(_all_stages)
        _out_results.resize(_iterations);
    else
        _out_results.resize(1);


    bool DEBUG = false;
    std::string prev_string = m_axiom;
    std::string new_string = "";
    int string_size;
    std::string m_key;
    bool no_def = true;


    srand (time(NULL)); //random
    //through iterations
    for(int i=0; i<_iterations;++i)
    {
        string_size= prev_string.size();
        //thought string_size
        for(int j=0;j<string_size;++j)
        {
            m_key = prev_string[j];
            //through m_Prules
            for(unsigned int k=0;k<m_Prules.size();++k)
            {   //check for non context sensitivity
                if((m_Prules[k].m_key==m_key)&& ((m_Prules[k].m_pre_condition=="")&&(m_Prules[k].m_post_condition=="")))
                {
                    //if stochastic
                    if(m_Prules[k].m_definitions.size()>1)
                    {
                        new_string += for0Lgen(m_Prules[k].m_definitions);

                    }
                    else //deterministic
                    {
                        auto iter=m_Prules[k].m_definitions.begin();
                        new_string += iter->first;

                    }
                    no_def=false;
                    break;
                }
            } //if no definition
            if(no_def==true)
            {
                new_string += m_key;

            }

            no_def=true;
        }
        if(DEBUG)
        {
            if(i==_iterations-1)
            {
                std::cout<<"\n0L system output:\n";
                std::cout<<new_string<<'\n';
            }

        }
        if(_all_stages)
            _out_results[i]=new_string;
        else if((!_all_stages)&&(i==_iterations-1))
            _out_results[0]=new_string;
        prev_string = new_string;
        new_string="";

    }
    return _out_results;
}
//----------------------------------------------------------------------------------------------------------------------
