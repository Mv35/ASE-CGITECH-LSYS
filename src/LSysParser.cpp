#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "LSysParser.h"
#include "LSys.h"
#include "LSysStructForFile.h"
#include "LSysStruct.h"
#include "ProductionRule.h"

LSysParser::LSysParser(){}


LSysStruct LSysParser::toParse(const char* file_name, LSysStruct &o_result, LSysStructForFile &lsys_parameters)
{

    o_result.axiom.clear();
    o_result.angle=30.0f;
    o_result.iteration=1;
    o_result.drawLenght=1.0f;
    o_result.Prules.clear();
    o_result.constants.clear();

    std::fstream my_file;
    std::string line;
    int count=0;
    char delimit = ' ';
    char end_of_line = ';';
    char chance_char ='(';
    std::string arrow = "->";
    //char pre_sym = '<';
    //char post_sym = '>';
    std::string token;
    int num_set=0;
    int last_num_set;
    int token_num;
    std::string tmp_key;
    std::string tmp_precondition;
    std::string tmp_postcondition;
    std::string tmp_defins;
    const char* tmp_chance_chr;
    float tmp_chance_f=1.0f;
    bool thereisPrule = false;

    my_file.open(file_name);

    if(my_file.is_open())
    {
        while(getline(my_file, line))
        {
            std::istringstream ss(line);
            //std::cout<<line<<'\n';
            token_num=0;
            int u_count=0;

            if (line=="axiom:")
               num_set=1;
            else if(line=="angle:")
                num_set=2;
            else if(line=="iterations:")
                num_set=3;
            else if(line=="scale:")
                num_set=4;
            else if(line=="constants:")
                num_set=5;
            else if(line=="Prules:")
                num_set=6;
            else if (line=="")
            {
                last_num_set = num_set;
                num_set=0;
            }

            switch(num_set)
            {
            case 1:
            {
                while(std::getline(ss, token, delimit))
                {
                    if((line!="axiom:") && (token[0]!=end_of_line))
                    {
                        o_result.axiom+=token[0];
                        //std::cout<<o_result.axiom<<'\n';
                    }
                    lsys_parameters.axiom=o_result.axiom;

                }
                break;
            }
            case 2:
            {
                while(std::getline(ss, token, delimit))
                {
                      if((line!="angle:") && (token[0]!=end_of_line) /*&& (token[0]!='0')*/)
                      {
                        std::stringstream stringToFloat(token);

                        if( !(stringToFloat >> o_result.angle))
                        {
                            o_result.angle=30.0f;
                        }
                      }

                    lsys_parameters.angle=o_result.angle;
                }
                break;
            }
            case 3:
            {
                 while(getline(ss, token, delimit))
                 {
                     if((line!="iterations:") && (token[0]!=end_of_line) /*&& (token[0]!='0')*/)
                     {
                         std::stringstream stringToInt(token);
                         if( !(stringToInt >> o_result.iteration) )
                         {
                             o_result.iteration =1;
                         }
                     }
                     lsys_parameters.iteration=o_result.iteration;
                 }
                 break;
            }
            case 4:
            {
                while(getline(ss,token, delimit))
                {
                    if((line!="scale:") && (token[0]!=end_of_line) /*&& (token[0]!='0')*/)
                    {
                        std::stringstream stringToFloat(token);

                        if( !(stringToFloat >> o_result.drawLenght) )
                        {
                            o_result.drawLenght=1.0f;
                        }
                    }

                    lsys_parameters.drawLenght= o_result.drawLenght;

                }
                break;
            }
            case 5:
            {
                while(getline(ss, token, delimit))
                {

                    if((line!="constants:") &&(token[0]!=end_of_line))
                    {
                        o_result.constants.push_back(token);
                        lsys_parameters.constants.push_back(token);
                    }
                }
                break;
            }
            case 6:
            {
                tmp_defins="";
                int Prules_counter= 0;
                ProductionRule p;

                while(std::getline(ss, token, delimit))
                {
                    //std::cout<<token<<'\n';
                    unsigned int pre_idx=0;
                    unsigned int post_idx=token.size();

                    if((line!="Prules:") && (token[0]!= end_of_line) && (token[0]!=chance_char) && (token!="->"))
                    {
                        if(u_count==0)
                        {
                            lsys_parameters.Prules.push_back(line);

                        }
                        u_count++;

                        for(unsigned int i=0; i<token.size();++i)
                        {
                            if(token[i]=='<')
                            {

                                pre_idx=i;
                                for(unsigned int j=0;j<i;++j)
                                {
                                    tmp_precondition+=token[j];
                                }
                            }

                            if(token[i]=='>')
                            {
                                post_idx=i;
                                for(unsigned int k=0;k<token.size();++k)
                                {
                                    tmp_postcondition+=token[k];
                                }
                            }
                        }

                        if(Prules_counter==0)
                        {
                            if((pre_idx==0 && post_idx==token.size()))
                            {
                                tmp_key=token;
                                std::cout<<"iltoken"<<token<<'\n';

                            }
                            else if((pre_idx!=0) && (post_idx==token.size()))
                            {
                                for(unsigned int l=pre_idx+1; l<token.size();++l)
                                {
                                    tmp_key+=token[l];
                                }
                            }
                            else if((pre_idx==0) && (post_idx!=token.size()))
                            {
                                for(unsigned int t=0; t<post_idx;++t)
                                {
                                    tmp_key+=token[t];
                                }
                            }
                            else if((pre_idx!=0) && (post_idx!=token.size()))
                            {
                                for(unsigned int q=pre_idx+1; q<post_idx;++q)
                                {
                                    tmp_key+=token[q];
                                }
                            }
                        }
                        else if(Prules_counter>0)
                        {
                            //for(unsigned int iq=0;iq<token.size()-1;++iq)

                                //tmp_defins+=token[iq];
                                tmp_defins+=token;
                                //std::cout<<"defins1"<<tmp_defins<<token<<'\n';
                        }
                        Prules_counter++;
                    }
                    if(token[0]==chance_char)
                    {
                        token.erase(token.size()-1);
                        tmp_chance_chr = &token[1];
                        tmp_chance_f = atof(tmp_chance_chr);
                    }

                }


                if(tmp_key!="")
                {

                    for(unsigned int i =0; i<o_result.Prules.size();++i)
                    {
                        //use vector::at for the fact it checks against bounds, where PRules[i] would have not
                        if( (o_result.Prules.at(i).key==tmp_key) && (o_result.Prules.at(i).pre_condition== tmp_precondition) && (o_result.Prules.at(i).post_condition==tmp_postcondition))
                        {
                            o_result.Prules[i].definitions[tmp_defins]= tmp_chance_f;
                            //std::cout<<tmp_defins<<"defins2"<<'\n';
                            thereisPrule =true;

                        }
                    }
                    if(!thereisPrule)
                    {
                        p.key=tmp_key;
                        p.definitions[tmp_defins]= tmp_chance_f;
                        p.pre_condition=tmp_precondition;
                        p.post_condition=tmp_postcondition;
                        o_result.Prules.push_back(p);
                        //std::reverse(o_result.Prules.begin(),o_result.Prules.end());
                        //std::cout<<p.key<<'\n'<<tmp_defins<<'\n';
                    }

                    tmp_postcondition="";
                    tmp_precondition="";
                    tmp_chance_f=1.0f;
                    tmp_defins="";
                    tmp_key="";
                    thereisPrule=false;
                }

                break;
            }
            }
            if(num_set==0)
            {
                num_set=last_num_set;
            }
            count++;
        }
    }
    my_file.close();

    for(unsigned i=0;i<o_result.Prules.size();++i)
    {
        int Prules_counter = o_result.Prules[i].definitions.size();

        if(Prules_counter>1)
        {
            o_result.Prules[i].definitions= definitionsNormalization(o_result.Prules[i].definitions);
        }
    }

    //o_result.LSysType= getLSysType(o_result.Prules);

    return o_result;
}

std::unordered_map<std::string, float> LSysParser::definitionsNormalization(std::unordered_map<std::string ,float> &defins)
{
    float sw=0.0f;

    for(auto iter=defins.begin(); iter!= defins.end(); ++iter)
    {
        sw+= iter->second;
    }

    for(auto iter=defins.begin(); iter!= defins.end(); ++iter)
    {
        iter->second/= sw;
    }
    return defins;
}

/*int LSysParser::getLSysType(std::vector<ProductionRule> &Prules)
{
    int current_ltype=0;

    for(unsigned i=0; i<Prules.size();++i)
    {
        if(Prules[i].definitions.size()>1)
        {
            if((current_ltype==0) || (current_ltype==3))
            {
                current_ltype+=1;
            }

            if((Prules[i].pre_condition!="") || (Prules[i].post_condition !=""))
            {
                if(current_ltype<3)
                {
                    current_ltype+=3;
                }
            }

        }
    }
    return (lsystype)current_ltype;
}

*/
