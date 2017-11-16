#include "LSys0L.h"
#include "LSys.h"
#include <iostream>
#include <stdlib.h>

LSys0L::LSys0L(const LSysStruct & s)
{
    m_axiom= s.axiom;
    m_angle= s.angle;
    m_scale= s.drawLenght;
    m_iterations= s.iteration;
    m_constants= s.constants;
    m_Prules= s.Prules;
}

LSys0L::~LSys0L(){std::cout << "deconstructor called\n";}


///@brief for Stochastic l-system : the definitions for a common symbol is chosen based on
/// their float value.

std::string LSys0L::for0Lgen(const std::unordered_map<std::string, float> &defins)
{
    std::string Definitions;

    float r = (float)(rand()%100) / 100;

    for(auto iter = defins.begin(); iter != defins.end(); ++iter)
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



///@brief the method
///
std::vector<std::string> LSys0L::develop(int iterations, std::vector<std::string> &out_results, bool all_stages)
{
    if(all_stages)
        out_results.resize(iterations);
    else
        out_results.resize(1);


    bool DEBUG = false;
    std::string prev_string = m_axiom;
    std::string new_string = "";
    int string_size;
    std::string key;
    bool no_def = true;


    srand (time(NULL));

    for(int i=0; i<iterations;++i)
    {
        string_size= prev_string.size();

        for(int j=0;j<string_size;++j)
        {
            key = prev_string[j];

            for(unsigned int k=0;k<m_Prules.size();++k)
            {
                if((m_Prules[k].key==key)&& ((m_Prules[k].pre_condition=="")&&(m_Prules[k].post_condition=="")))
                {

                    if(m_Prules[k].definitions.size()>1)
                    {
                        new_string += for0Lgen(m_Prules[k].definitions);

                    }
                    else
                    {
                        auto iter=m_Prules[k].definitions.begin();
                        new_string += iter->first;

                    }
                    no_def=false;
                    break;
                }
            }
            if(no_def==true)
            {
                new_string += key;

            }

            no_def=true;
        }
        if(DEBUG)
        {
            if(i==iterations-1)
            {
                std::cout<<"\n0L system output:\n";
                std::cout<<new_string<<'\n';
            }

        }
        if(all_stages)
            out_results[i]=new_string;
        else if((!all_stages)&&(i==iterations-1))
            out_results[0]=new_string;
        prev_string = new_string;
        new_string="";

    }
    return out_results;
}
