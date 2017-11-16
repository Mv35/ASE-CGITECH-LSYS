
#include <iostream>
#include <algorithm>
#include <math.h>
#include <ngl/Util.h>  //TWO_PI
#include <ngl/VAOPrimitives.h>
#include <ngl/Mat4.h>
#include "TurtleBranch.h"
#include "TurtleNodes.h"
#include "Turtle.h"

#define _USE_MATH_DEFINE //Required for M_PI

Turtle::Turtle()
{
    Turtle::m_lSys="abc";
    Turtle::m_iteration=5;
    m_angle = (45.0f*M_PI)/180.0f;
    m_step=0.5f;
    m_start_x=0.0f;
    m_start_y=0.0f;
    m_start_z=0.0f;
}

Turtle::Turtle(TurtleParameters p)
{
    Turtle::m_iteration= p.iteration;
    Turtle::m_lSys= p.lSys[m_iteration];
    Turtle::m_dictSymbols= p.dictSymbols;
    m_variables = p.dictSymbols;
    m_angle = (p.angle*M_PI)/180;
    m_step= p.drawLenght;
    m_start_x=p.startX;
    m_start_y=p.startY;
    m_start_z=p.startZ;
    m_constants=p.constants;

    //to do add constants to variable

}


//mutators and accessors


void Turtle::setAngleInDeg(float deg)
{
    m_angle=(deg*M_PI)/180;
}

void Turtle::setAngleInRad(float rad)
{
    m_angle=rad;
}

void Turtle::setIteration(int itera)
{
    m_iteration=itera;

}

void Turtle::setStartX(float xc)
{
    m_start_x=xc;
}

void Turtle::setStartY(float yc)
{
    m_start_y=yc;
}

void Turtle::setStartZ(float zc)
{
    m_start_z=zc;
}

void Turtle::setdrawStep(float st)
{
    m_step=st;
}



float Turtle::getAngleInDeg()
{
    return (m_angle*180)/M_PI;

}

float Turtle::getAngleInRad()
{
    return m_angle;

}

float Turtle::getIteration()
{
    return m_iteration;
}

float Turtle::getStartX()
{
    return m_start_x;

}

float Turtle::getStartY()
{
    return m_start_y;
}

float Turtle::getStartZ()
{
    return m_start_z;
}

float Turtle::getdrawStep()
{
    return m_step;
}

TreeData Turtle::interpret(int segType)//, float radius, int geodiv)
{
    TreeData tree;
    tree.drawType = segType;


    std::vector<TurtleNodes> tNodes;
    TurtleNodes currentNode;
    std::vector<int> indexData;
    ngl::Vec4 p, n, to, from, to2, from2, toNext, fromNext, p1p2, p2p3, r, s, r2, s2, rAvg, sAvg;
    int divisions = 8;
    float tRadius=  0.03f;
    double alpha= ngl::TWO_PI/divisions;
    int tBegin;
    int tEnd;

    //variables for branched structures
    bool tBracketOff = false;
    int tBracketOffInt =0;

    std::vector<TurtleBranch> branch;
    TurtleBranch currentBranch;
    std::vector<ngl::Mat4> tmatrices;
    ngl::Vec4 tposition (0.0,0.0,0.0,1.0);
    ngl::Vec4 prev_tposition(getStartX(),getStartY(),getStartZ(),1.0);
    ngl::Vec4 tdirection (0.0,1.0,0.0,0.0);
    ngl::Vec4 twdirection (1.0,0.0,0.0,0.0);
    ngl::Vec4 prev_twdirection;
    ngl::Vec4 tex(0.0,0.0,0.0,1.0);
    float an = getAngleInDeg();
    float st = getdrawStep();
    char ctoken;
    bool turtleDown=true;

    ngl::Mat4 rotationMat;
    ngl::Mat4 xRot;
    ngl::Mat4 yRot;
    ngl::Mat4 zRot;

    int ind=0;
    bool goParent=true;

    currentNode.position=tposition;
    currentNode.drawStep=st;
    currentNode.previousDirection=tdirection;
    tNodes.push_back(currentNode);
    indexData.push_back(ind);

    for(unsigned int i=0;i<m_lSys.size();++i)
    {
        ctoken=m_lSys[i];
        turtleDown=true;
        for(unsigned int j=0;j<m_variables.size();++j)
        {
            if(ctoken==m_variables[j][0])
            {
                turtleDown=false;

                if(ctoken=='f')
                {
                    tposition = (tdirection*-st)+prev_tposition;
                    prev_tposition=tposition;
                    break;
                }
                else if(ctoken=='+')
                {
                    zRot.rotateZ(an);
                    rotationMat *= zRot;
                    //std::cout<<"+symbolfound"<<'\n';
                    break;
                }
                else if(ctoken=='-')
                {
                    zRot.rotateZ(-an);
                    rotationMat *= zRot;
                    break;
                }
                else if(ctoken=='^')
                {
                    xRot.rotateX(an);
                    rotationMat *= xRot;
                    break;
                }
                else if(ctoken=='&')
                {
                    xRot.rotateX(-an);
                    rotationMat *= xRot;
                    break;
                }
                else if((ctoken=='>') || (ctoken=='/'))
                {
                    yRot.rotateY(an);
                    rotationMat *=yRot;
                    break;
                }
                else if((ctoken=='<') || (ctoken==','))
                {
                    yRot.rotateY(-an);
                    rotationMat *= yRot;
                    break;

                }
                else if(ctoken=='!')
                {
                    st*=1.2;
                    tRadius*=2;
                    break;
                }
                else if(ctoken=='~')
                {
                    st/=1.2;
                    tRadius/=2;
                    break;
                }
                else if(ctoken=='[')
                {
                    if(goParent)
                    {
                        currentBranch.index =ind;

                    }
                    else
                    {
                        currentBranch.index = currentBranch.index;
                    }
                    currentBranch.previousDirection = twdirection;

                    currentBranch.position= tposition;
                    currentBranch.rotationMatrix= rotationMat;
                    currentBranch.drawStep = st;
                    currentBranch.pRadius = tRadius;
                    currentBranch.colour = tex;
                    branch.push_back(currentBranch);
                    break;
                }
                else if(ctoken==']')
                {
                    currentBranch=branch.back();
                    branch.pop_back();
                    tposition=currentBranch.position;
                    rotationMat=currentBranch.rotationMatrix;
                    st=currentBranch.drawStep;
                    tRadius=currentBranch.pRadius;
                    tex=currentBranch.colour;
                    twdirection=currentBranch.previousDirection;

                    indexData.at(indexData.size()-1) = currentBranch.index;
                    tree.colours.push_back(tex);
                    tBracketOffInt =1;

                    prev_tposition = tposition;
                    goParent = false;
                    break;


                }
                else if(ctoken=='C')
                {
                    i++;
                    break;
                }

            }



        if(turtleDown)

        {
            xRot.identity();
            yRot.identity();
            zRot.identity();

            tmatrices.push_back(rotationMat);

            prev_twdirection = twdirection;
            if(prev_twdirection.length() != 0.0)
                prev_twdirection.normalize();

            twdirection = tdirection*rotationMat;

            if(twdirection.length() != 0.0)
                twdirection.normalize();
            tposition = (twdirection*st)+prev_tposition;

            currentNode.position=tposition;
            currentNode.drawStep=st;
            currentNode.pRadius=tRadius;
            currentNode.previousDirection=prev_twdirection;
            currentNode.closingBracket=tBracketOffInt;
            tNodes.push_back(currentNode);

            indexData.push_back(++ind);
            indexData.push_back(ind);

            tree.colours.push_back(tex);

            prev_tposition = tposition;

            tree.colours.push_back(tex);

            prev_tposition = tposition;
            goParent =true;
            tBracketOffInt=0;
        }
    }
    }

    if(segType==1)
    {
        tree.points.resize(tNodes.size());
        for(unsigned k=0;k<tNodes.size();++k)
        {
            tree.points.at(k)=tNodes[k].position;
        }

        tree.indices = indexData;

        return tree;
    }
    else
    {
        tree.positions.reserve(tNodes.size());
        for(unsigned int nodeC=0;nodeC<tNodes.size();++nodeC)
            tree.positions[nodeC]= tNodes[nodeC].position;

        tree.lineIndices = indexData;
    }

    //need to check math for 3d mesh


/*  if(
    for(unsigned points=1;points<indexData.size();points+=2)
    {
        from = tNodes[indexData[points-1]].position;
        to = tNodes[indexData[points]].position;

        if(points==1)
            from2=from;
        else
            from2=from+(to-from)*(tNodes[indexData[points-1]].pRadius);

        to2 = from+(to-from)*(1-(tNodes[indexData[points]].pRadius));
        p1p2=to-from;

        if(p1p2.length() != 0.0)
            p1p2.normalize();

        if(prev_twdirection.length() != 0.0)
            prev_twdirection.normalize();

        if(p1p2 != prev_twdirection)
            r=p1p2.cross(prev_twdirection);

        if(r.length() != 0.0)
            r.normalize();

        s=p1p2.cross(r);

        if(s.length() != 0.0)
            s.normalize();

        tBegin = tree.points.size();
        for(float beta=0;beta<2*M_PI;beta+=alpha)
        {

            p= from2 +(tNodes[indexData[points-1]].pRadius)*r*cos(beta) + (tNodes[indexData[points-1]].pRadius)*s*sin(beta);
            tree.points.push_back(p);

            n = p - tNodes[indexData[points-1]].position;
            if(n.length()!=0.0)
                n.normalize();
            tree.normals.push_back(n);

            p = to2 + (tNodes[indexData[points]].pRadius)*r * cos(beta) + (tNodes[indexData[points]].pRadius)*s* sin(beta);
            tree.points.push_back(p);

            n = p-tNodes[indexData[points]].position;
            if(n.length() != 0.0)
                n.normalize();
            tree.normals.push_back(n);

            if(tNodes[indexData[points]].closingBracket)
                tBracketOff=true;

        }
        tEnd = tree.points.size()-1;

        for(int inds=tBegin;inds<tEnd-2;inds+=2)
        {
            tree.indices.push_back(inds);
            tree.indices.push_back(inds+1);
            tree.indices.push_back(inds+2);
            tree.indices.push_back(inds+3);
            tree.indices.push_back(inds+2);
            tree.indices.push_back(inds+1);
        }

        tree.indices.push_back(tEnd-1);
        tree.indices.push_back(tEnd);
        tree.indices.push_back(tBegin+1);

        tree.indices.push_back(tBegin);
        tree.indices.push_back(tBegin+1);
        tree.indices.push_back(tEnd-1);

      }
*/
     return tree;
}

