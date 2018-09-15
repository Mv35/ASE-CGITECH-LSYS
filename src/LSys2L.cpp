


#include "LSys.h"
#include "LSys0L.h"
#include "LSys2L.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//copy ctor
LSys2L::LSys2L(const LSysStruct & s) : LSys0L(s)
{
    m_axiom= s.m_axiom;
    m_angle= s.m_angle;
    m_scale= s.m_drawLenght;
    m_iterations= s.m_iteration;
    m_constants= s.m_constants;
    m_Prules= s.m_Prules;
}
//----------------------------------------------------------------------------------------------------------------------
// method that allows the generation of all the different kinds of LSystems D0, D1, D2 , 0L, 1L and 2L according to the Prules passed
std::vector<std::string> LSys2L::develop(int iterations, std::vector<std::string> &_out_results, bool _all_stages)
{
    // Resizing the vector depending on whether
      // the user wants all the stages or just the final one
      if(_all_stages)
        _out_results.resize(iterations);
      else
        _out_results.resize(1);

      // Temporary variables and flags
      bool DEBUG = false;
      std::string prev_string = m_axiom;
      std::string new_string = "";
      int string_size;
      std::string key;
      bool no_def = true;
      int using_rule=-1;


      std::unordered_map<std::string, float>::iterator it;

      srand ( time(NULL) ); //randomness

      // looping through the iterations
      for(int ii=0;ii<iterations;++ii)
      {
        string_size = prev_string.size();


        // looping through the whole string
        for(int jj=0;jj<string_size;++jj)
        {
          key = prev_string[jj];

          // looping through all of the rules chcecking for double context-sensitive
          for(unsigned int kk=0;kk<m_Prules.size();++kk)
          {
            if((m_Prules[kk].m_pre_condition != "") && (m_Prules[kk].m_post_condition!=""))
            {
              if((m_Prules[kk].m_key==key) && ((m_Prules[kk].m_pre_condition[0]==prev_string[jj-1])&&(m_Prules[kk].m_post_condition[0]==prev_string[jj+1])))
              {
                /// Looping through all the definitions of the selected
                /// rule to make sure they don't all have a zero weight
                for(it = m_Prules[kk].m_definitions.begin();it != m_Prules[kk].m_definitions.end();++it)
                {
                  if(it->second != 0.0)
                  {
                    using_rule = kk;
                    no_def = false;
                    break;
                  }
                }
              }
            }
          }

          //if double condition was not found, search for single
          if(no_def==true)
          {
            for(unsigned int xx=0;xx<m_Prules.size();++xx)
            {
              if((m_Prules[xx].m_pre_condition != "") && (m_Prules[xx].m_post_condition == ""))
              {
                if((m_Prules[xx].m_key==key)&&(m_Prules[xx].m_pre_condition[0]==prev_string[jj-1]))
                {
                  for(it = m_Prules[xx].m_definitions.begin();it != m_Prules[xx].m_definitions.end();++it)
                  {
                    if(it->second != 0.0)
                    {
                      using_rule = xx;
                      no_def = false;
                      break;
                    }
                  }
                }
              }else if((m_Prules[xx].m_pre_condition == "") && (m_Prules[xx].m_post_condition != ""))
              {
                if((m_Prules[xx].m_key==key)&&(m_Prules[xx].m_post_condition[0]==prev_string[jj+1]))
                {
                  for(it = m_Prules[xx].m_definitions.begin();it != m_Prules[xx].m_definitions.end();++it)
                  {
                    if(it->second != 0.0)
                    {
                      using_rule = xx;
                      no_def = false;
                      break;
                    }
                  }
                }
              }
            }
          }

          // If no context-sensitive rule was found, check context-free ones
          if(no_def==true)
          {
            // looping through all of the rules checking for context-free
            for(unsigned int qq=0;qq<m_Prules.size();++qq)
            {
              if( (m_Prules[qq].m_key==key) && ((m_Prules[qq].m_pre_condition=="")&&(m_Prules[qq].m_post_condition=="")) )
              {
                for(it = m_Prules[qq].m_definitions.begin();it != m_Prules[qq].m_definitions.end();++it)
                {
                  if(it->second != 0.0)
                  {
                    using_rule = qq;
                    no_def = false;
                    break;
                  }
                }
              }
            }
          }

          if(using_rule != -1)
          {
            /// Checking for more than 1 definition in the current rule
            /// Applying the stochastic algorithm
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
          if(ii==iterations-1)
          {
            std::cout<<"\n2L System output:\n";
            std::cout<<new_string<<std::endl;
          }
        }

        // Stores the strings into the output vector according to the all_stages value
        if(_all_stages)
          _out_results[ii]=new_string;

        if((!_all_stages)&&(ii==iterations-1))
          _out_results[0]=new_string;

        // Setting up values for next iteration
        prev_string = new_string;
        new_string = "";

      }

      return _out_results;
}
