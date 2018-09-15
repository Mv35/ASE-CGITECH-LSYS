

#include "LSys.h"
#include "LSys0L.h"
#include "LSys1L.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------

LSys1L::LSys1L(const LSysStruct & s) : LSys0L(s)
{
    m_axiom= s.m_axiom;
    m_angle= s.m_angle;
    m_scale= s.m_drawLenght;
    m_iterations= s.m_iteration;
    m_constants= s.m_constants;
    m_Prules= s.m_Prules;
}
//LSys1L::~LSys1L(){std::cout << "1Ldeconstructor called\n";}

//----------------------------------------------------------------------------------------------------------------------

std::vector<std::string> LSys1L::develop(int _iterations, std::vector<std::string> &_out_results, bool _all_stages)
{
    if(_all_stages)
        _out_results.resize(_iterations);
    else
        _out_results.resize(1);


    bool DEBUG = false;
    std::string prev_string = m_axiom;
    std::string new_string = "";
    int string_size;
    std::string key;
    bool no_def = true;

    int using_rule=-1;
    char sensitive_side='0';

    std::unordered_map<std::string, float>::iterator it;

    srand (time(NULL));

    //Defining which side we would be working on.
    //As 1L cannot handle sensitive conditions on both sides of the key.
    for(unsigned int uu=0;uu<m_Prules.size();++uu)
    {
      if((m_Prules[uu].m_pre_condition!="")||(m_Prules[uu].m_post_condition!=""))
      {
        // Allowing this to work only on sigle-sided conditions
        if((m_Prules[uu].m_pre_condition!="") && (m_Prules[uu].m_post_condition==""))
        {
          sensitive_side='l';
          break;
        }else if((m_Prules[uu].m_pre_condition=="") && (m_Prules[uu].m_post_condition!=""))
        {
          sensitive_side='r';
          break;
        }
      }
    }


    // looping through all the iterations
    for(int ii=0;ii<_iterations;++ii)
    {
      string_size = prev_string.size();


      // looping through the whole string in the current step
      for(int jj=0;jj<string_size;++jj)
      {
        key = prev_string[jj];

        // looping through all of the rules chcecking for context-sensitive
        for(unsigned int kk=0;kk<m_Prules.size();++kk)
        {
          //context-sensitive rules have priority over context-free
          switch (sensitive_side)
          {
          case 'l': // only consider pre-conditions
          {
            if((m_Prules[kk].m_pre_condition != "") && (m_Prules[kk].m_post_condition==""))
            {
              if((m_Prules[kk].m_key==key) && (m_Prules[kk].m_pre_condition[0]==prev_string[jj-1]))
              {
                /// Checking that atleast one weight is not zero
                for(it = m_Prules[kk].m_definitions.begin();it != m_Prules[kk].m_definitions.end();++it)
                {
                  if(it->second != 0.0)
                  {
                    using_rule = kk;
                  }
                }
              }
            }
            break;
          }
          case 'r': // only consider post-conditions
          {
            if( (m_Prules[kk].m_post_condition != "") && (m_Prules[kk].m_pre_condition == ""))
            {
              if((m_Prules[kk].m_key==key)&&(m_Prules[kk].m_post_condition[0]==prev_string[jj+1]))
              {
                /// Checking that atleast one weight is not zero
                for(it = m_Prules[kk].m_definitions.begin();it != m_Prules[kk].m_definitions.end();++it)
                {
                  if(it->second != 0.0)
                  {
                    using_rule = kk;
                  }
                }
              }
            }
            break;
          }
          }
        }


        // If no context-sensitive rule was found, check context-free ones
        if(using_rule == -1)
        {
          // looping through all of the rules checking for context-free
          for(unsigned int qq=0;qq<m_Prules.size();++qq)
          {
            if( (m_Prules[qq].m_key==key) && ((m_Prules[qq].m_pre_condition=="")&&(m_Prules[qq].m_post_condition=="")) )
            {
              /// Checking that atleast one weight is not zero
              for(it = m_Prules[qq].m_definitions.begin();it != m_Prules[qq].m_definitions.end();++it)
              {
                if(it->second != 0.0)
                {
                  using_rule = qq;
                  break;
                }
              }
            }
          }
        }

        if(using_rule != -1)
        {
          /// Stochastic random procedure based on probabilities
          if(m_Prules[using_rule].m_definitions.size()>1)
          {
            //calling the function which returns the correct stochastic value
            new_string += for0Lgen(m_Prules[using_rule].m_definitions);

          }else{
            it = m_Prules[using_rule].m_definitions.begin();
            new_string += it->first;
          }

          no_def = false;
        }

        //if the current symbol has no definition
        if(no_def==true)
        {
          new_string += key;
        }

        using_rule = -1;    //resetting using_rule index flag
        no_def=true;    //resetting no definition flag
      }

      if(DEBUG)
      {
        if(ii==_iterations-1)
        {
          std::cout<<"\n1L System output:\n";
          std::cout<<new_string<<std::endl;
        }
      }

      // Stores the strings into the output vector according to the all_stages value
      if(_all_stages)
        _out_results[ii]=new_string;

      if((!_all_stages)&&(ii==_iterations-1))
        _out_results[0]=new_string;

      // Setting up values for next iteration
      prev_string = new_string;
      new_string = "";

    }

    return _out_results;

}
//----------------------------------------------------------------------------------------------------------------------
