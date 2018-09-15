
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
//default constructor
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
// copy constructor
//----------------------------------------------------------------------------------------------------------------

Turtle::Turtle(TurtleParameters p)
{
    Turtle::m_iteration= p.m_iteration;
    Turtle::m_lSys= p.m_lSys[m_iteration];
    Turtle::m_dictSymbols= p.m_dictSymbols;
    m_variables = p.m_dictSymbols;
    m_angle = (p.m_angle*M_PI)/180;
    m_step= p.m_drawLenght;
    m_start_x=p.m_startX;
    m_start_y=p.m_startY;
    m_start_z=p.m_startZ;
    m_constants=p.m_constants;

    //to do add constants to variable
    for(unsigned i=0; i<m_constants.size();++i)
    {
      m_variables.push_back(m_constants[i]);
    }
}

//----------------------------------------------------------------------------------------------------------------


//mutators and accessors


void Turtle::setAngleInDeg(float deg)
{
    m_angle=(deg*M_PI)/180;
}

//----------------------------------------------------------------------------------------------------------------

void Turtle::setAngleInRad(float rad)
{
    m_angle=rad;
}

//----------------------------------------------------------------------------------------------------------------

void Turtle::setIteration(int itera)
{
    m_iteration=itera;

}

//----------------------------------------------------------------------------------------------------------------

void Turtle::setStartX(float xc)
{
    m_start_x=xc;
}

//----------------------------------------------------------------------------------------------------------------

void Turtle::setStartY(float yc)
{
    m_start_y=yc;
}

//----------------------------------------------------------------------------------------------------------------

void Turtle::setStartZ(float zc)
{
    m_start_z=zc;
}

//----------------------------------------------------------------------------------------------------------------

void Turtle::setdrawStep(float st)
{
    m_step=st;
}

//----------------------------------------------------------------------------------------------------------------

float Turtle::getAngleInDeg()
{
    return (m_angle*180)/M_PI;

}

//----------------------------------------------------------------------------------------------------------------

float Turtle::getAngleInRad()
{
    return m_angle;

}

//----------------------------------------------------------------------------------------------------------------

float Turtle::getIteration()
{
    return m_iteration;
}

//----------------------------------------------------------------------------------------------------------------

float Turtle::getStartX()
{
    return m_start_x;

}

//----------------------------------------------------------------------------------------------------------------

float Turtle::getStartY()
{
    return m_start_y;
}

//----------------------------------------------------------------------------------------------------------------

float Turtle::getStartZ()
{
    return m_start_z;
}

//----------------------------------------------------------------------------------------------------------------

float Turtle::getdrawStep()
{
    return m_step;
}

//----------------------------------------------------------------------------------------------------------------
//method to interpret an LSystem result string and to generate the geometry
TreeData Turtle::interpret(float _radius, int _divisions)
{
    TreeData tree;
    int segType =2;
    tree.drawType = segType;


    std::vector<TurtleNodes> tNodes;
    TurtleNodes currentNode;
    std::vector<int> indexData;
    ngl::Vec4 p, n, to, from, to2, from2, p1p2, r, s;
    int divisions = _divisions;//4;
    float pRadius=  _radius;//0.03f;
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
    //std::cout<<st<<"drawstep"<<'\n';
    //float st = 0.01;
    char ctoken;
    bool turtleDown=true;

    ngl::Mat4 rotationMat;
    ngl::Mat4 xRot;
    ngl::Mat4 yRot;
    ngl::Mat4 zRot;

    int ind=0;
    bool goParent=true;

    //origin point
    currentNode.m_position=tposition;
    currentNode.m_drawStep=st;
    currentNode.m_previousDirection=tdirection;
    tNodes.push_back(currentNode);
    indexData.push_back(ind);

//std::cout<<indexData[0]<<'\n';
    //going through the resulting LSystem string size
    for(unsigned int i=0;i<m_lSys.size();++i)
    {
        ctoken=m_lSys[i];
        //std::cout<<m_lSys<<'\n';
        turtleDown=true;
        //through all the variables
        for(unsigned int j=0;j<m_variables.size();++j)
        {
            //if not drawing symbol
            if(ctoken==m_variables[j][0])
            {
                turtleDown=false;

                if(ctoken=='f') //step without draw
                {
                    tposition = (tdirection*-st)+prev_tposition;
                    prev_tposition=tposition;
                    break;
                }
                else if(ctoken=='+') //positive z rotation
                {
                    zRot.rotateZ(an);
                    rotationMat *= zRot;
                    //std::cout<<"+symbolfound"<<'\n';
                    break;
                }
                else if(ctoken=='-') //negative z rotation
                {
                    zRot.rotateZ(-an);
                    rotationMat *= zRot;
                    break;
                }
                else if(ctoken=='^') // positive x rotation
                {
                    xRot.rotateX(an);
                    rotationMat *= xRot;
                    break;
                }
                else if(ctoken=='&') // negative x rotation
                {
                    xRot.rotateX(-an);
                    rotationMat *= xRot;
                    break;
                }
                else if((ctoken=='>') || (ctoken=='/')) //positive y rotation
                {
                    yRot.rotateY(an);
                    rotationMat *=yRot;
                    break;
                }
                else if((ctoken=='<') || (ctoken==',')) //negative y rotation
                {
                    yRot.rotateY(-an);
                    rotationMat *= yRot;
                    break;

                }
                else if(ctoken=='!') //increase stepsize and radius every iteration
                {
                    st*=1.2;
                    pRadius*=2;
                    break;
                }
                else if(ctoken=='~') //reduce stepsize and radius every iteration
                {
                    st/=1.2;
                    pRadius/=2;
                    break;
                }
                else if(ctoken=='[') //starting branch push
                {
                    if(goParent)
                    {
                        currentBranch.m_index =ind;

                    }
                    else
                    {
                        currentBranch.m_index = currentBranch.m_index;
                    }
                    currentBranch.m_previousDirection = twdirection;

                    currentBranch.m_position= tposition;
                    currentBranch.m_rotationMatrix= rotationMat;
                    currentBranch.m_drawStep = st;
                    currentBranch.m_pRadius = pRadius;
                    currentBranch.m_colour = tex;
                    branch.push_back(currentBranch);
                    break;
                }
                else if(ctoken==']') //closing branch pop
                {
                    currentBranch=branch.back();
                    branch.pop_back();
                    tposition=currentBranch.m_position;
                    rotationMat=currentBranch.m_rotationMatrix;
                    st=currentBranch.m_drawStep;
                    pRadius=currentBranch.m_pRadius;
                    tex=currentBranch.m_colour;
                    twdirection=currentBranch.m_previousDirection;

                    indexData.at(indexData.size()-1) = currentBranch.m_index;
                    tree.m_colours.push_back(tex);
                    tBracketOffInt =1;

                    prev_tposition = tposition;
                    goParent = false;
                    break;


                }
                else if(ctoken=='C') //color need implementation
                {
                    i++;
                    break;
                }

            }


        }
        if(turtleDown) //if drawing symbol

        {
            //set individual matrices to identity
            xRot.identity();
            yRot.identity();
            zRot.identity();
            //push rotation matrix for each point
            tmatrices.push_back(rotationMat);

            prev_twdirection = twdirection;
            //chech not = 0
            if(prev_twdirection.length() != 0.0)
                prev_twdirection.normalize();

            twdirection = tdirection*rotationMat;
            //chech not = 0
            if(twdirection.length() != 0.0)
                twdirection.normalize();
            tposition = (twdirection*st)+prev_tposition;

            //store the point
            currentNode.m_position=tposition;
            currentNode.m_drawStep=st;

            currentNode.m_pRadius=pRadius;


            currentNode.m_previousDirection=prev_twdirection;
            currentNode.m_closingBracket=tBracketOffInt;
            tNodes.push_back(currentNode);

            //store indexes
            indexData.push_back(++ind);

            indexData.push_back(ind);


            tree.m_colours.push_back(tex);

            prev_tposition = tposition;

            tree.m_colours.push_back(tex);

            prev_tposition = tposition;
            goParent =true;
            tBracketOffInt=0;
        }

     }

    if(segType!=2) //line indeces, for line mesh
    {
        tree.m_points.resize(tNodes.size());
        for(unsigned k=0;k<tNodes.size();++k)
        {
            tree.m_points.at(k)=tNodes[k].m_position;
        }

        tree.m_indices = indexData;

        return tree;
    }
    else //3dmesh
    {
        tree.m_positions.reserve(tNodes.size());
        for(unsigned int nodeC=0;nodeC<tNodes.size();++nodeC)
            tree.m_positions[nodeC]= tNodes[nodeC].m_position;

        tree.m_lineIndices = indexData;
        //std::cout<<"tree lineIndeces"<<tree.lineIndices[1]<<'\n';
    }

    //3d mesh


    if(segType==2)
        for(unsigned points=1;points<indexData.size();points+=2)
        {
            from = tNodes[indexData[points-1]].m_position;
            to = tNodes[indexData[points]].m_position;

            //ra
            tNodes[indexData[0]].m_pRadius=pRadius;

            //start at origin
            if(points==1)
            {
               from2=from;

            }
            else
                from2=from+(to-from)*(tNodes[indexData[points-1]].m_pRadius);

            //destination
            to2 = from+(to-from)*(1-(tNodes[indexData[points]].m_pRadius));
            p1p2=to-from;
            //chech not = 0
            if(p1p2.length() != 0.0)
                p1p2.normalize();
            //chech not = 0
            if(prev_twdirection.length() != 0.0)
                prev_twdirection.normalize();
            //chech not = previous world direction
            if(p1p2 != prev_twdirection)
                r=p1p2.cross(prev_twdirection);
                if(r.m_x==0 && r.m_y==0 && r.m_z == 0)
                {
                    r.m_z = -1.0f;

                }
            //chech not = 0
            if(r.length() != 0.0)
                r.normalize();

            s=p1p2.cross(r);
            //chech not = 0
            if(s.length() != 0.0)
                s.normalize();
            //start of the cylinder

            tBegin = tree.m_points.size();

            for(float beta=0;beta<2*M_PI;beta+=alpha)
            {

                //bottom base points
                p= from2 +(tNodes[indexData[points-1]].m_pRadius)*r*cos(beta) + (tNodes[indexData[points-1]].m_pRadius)*s*sin(beta);
                tree.m_points.push_back(p);


                n = p - tNodes[indexData[points-1]].m_position;
                if(n.length()!=0.0)
                    n.normalize();
                tree.m_normals.push_back(n);
                //top base points
                p = to2 + (tNodes[indexData[points]].m_pRadius)*r * cos(beta) + (tNodes[indexData[points]].m_pRadius)*s* sin(beta);
                tree.m_points.push_back(p);

                n = p-tNodes[indexData[points]].m_position;
                if(n.length() != 0.0)
                    n.normalize();
                tree.m_normals.push_back(n);

                if(tNodes[indexData[points]].m_closingBracket)
                    tBracketOff=true;

            }

            tEnd = tree.m_points.size()-1;
            //storing indexes
            for(int inds=tBegin;inds<tEnd-2;inds+=2)
            {

                tree.m_indices.push_back(inds);
                tree.m_indices.push_back(inds+1);
                tree.m_indices.push_back(inds+2);
                tree.m_indices.push_back(inds+2);
                tree.m_indices.push_back(inds+1);
                tree.m_indices.push_back(inds+3);

            }

            //Stitching the last two triangles
            tree.m_indices.push_back(tEnd-1);
            tree.m_indices.push_back(tEnd);
            tree.m_indices.push_back(tBegin);

            tree.m_indices.push_back(tBegin);
            tree.m_indices.push_back(tEnd);
            tree.m_indices.push_back(tBegin+1);



            /// Computing Sphere at the end of each cylinder (beta) needs northpole closed and fixed

            for(int slice=0;slice<divisions;++slice)
            {
              for(int stack=1;stack<divisions;++stack)
              {
                p.m_x = tNodes[indexData[points]].m_position[0]+((sin((M_PI*stack)/divisions)) * (cos( ((2*M_PI)*slice) / divisions ) ) ) * tNodes[indexData[points]].m_pRadius;
                p.m_y = tNodes[indexData[points]].m_position[1]+((sin((M_PI*stack)/divisions)) * (sin( ((2*M_PI)*slice) / divisions ) ) ) * tNodes[indexData[points]].m_pRadius;
                p.m_z = tNodes[indexData[points]].m_position[2]+(cos((M_PI*stack)/divisions)) * tNodes[indexData[points]].m_pRadius;
                tree.m_points.push_back(p);

                //Finding the normal for this vertex of the sphere
                n = p - tNodes[indexData[points]].m_position;
                if(n.length() != 0.0)
                  n.normalize();
                tree.m_normals.push_back(n);
              }

              //fixing the sphere indices
              if(slice>0)
              {
                for(int seg=0;seg<divisions-2;++seg)
                {
                  tree.m_indices.push_back(tree.m_points.size()-((divisions-1)*2)+seg);
                  tree.m_indices.push_back(tree.m_points.size()-((divisions-1)*2 -1)+seg);
                  tree.m_indices.push_back(tree.m_points.size()-(divisions-1)+seg);

                  tree.m_indices.push_back(tree.m_points.size()-(divisions-2)+seg);
                  tree.m_indices.push_back(tree.m_points.size()-(divisions-1)+seg);
                  tree.m_indices.push_back(tree.m_points.size()-((divisions-1)*2 -1)+seg);


                }


              }
            //for(unsigned i=0; i< tree.indices.size();i+=3)
                 //std::cout<<tree.indices[i]<<tree.indices[i+1]<<tree.indices[i+2]<<'\n';
            }

            //filling in the final segment of the sphere
            for(int seg=0;seg<divisions-2;++seg)
            {
              tree.m_indices.push_back((tree.m_points.size()-(divisions-1)) +seg );
              tree.m_indices.push_back((tree.m_points.size()-(divisions-2)) +seg );
              tree.m_indices.push_back((tree.m_points.size()-((divisions-1)*divisions) +seg));

              tree.m_indices.push_back((tree.m_points.size()-((divisions-1)*divisions) +seg +1)) ;
              tree.m_indices.push_back((tree.m_points.size()-((divisions-1)*divisions) +seg));
              tree.m_indices.push_back((tree.m_points.size()-(divisions-2)) +seg );

            }
            //std::cout<<tree.indices.size()<<'\n';
            //for(unsigned i=0; i< tree.indices.size();i+=3)
              // std::cout<<tree.indices[i]<<tree.indices[i+1]<<tree.indices[i+2]<<'\n';
            p.m_x = tNodes[indexData[points]].m_position[0];
            p.m_y = tNodes[indexData[points]].m_position[1];
            p.m_z = tNodes[indexData[points]].m_position[2]+tNodes[indexData[points]].m_pRadius;
            tree.m_points.push_back(p);

            //Finding the normal for the pole vertex of the sphere
            n = p - tNodes[indexData[points]].m_position;
            if(n.length() != 0.0)
              n.normalize();
            tree.m_normals.push_back(n);

            p.m_x = tNodes[indexData[points]].m_position[0];
            p.m_y = tNodes[indexData[points]].m_position[1];
            p.m_z = tNodes[indexData[points]].m_position[2]-tNodes[indexData[points]].m_pRadius;
            tree.m_points.push_back(p);

            //Finding the normal for the pole vertex of the sphere
            n = p - tNodes[indexData[points]].m_position;
            if(n.length() != 0.0)
              n.normalize();
            tree.m_normals.push_back(n);


            // Closing the start and the end of the sphere with gl_triangles
            for(int row=0; row<divisions;++row)
            {
              //Closing South-pole
              tree.m_indices.push_back(tree.m_points.size()-2); //south pole point
              tree.m_indices.push_back(tree.m_points.size() - (divisions*(divisions-1)+2) + (divisions-1)*row );
              if(row<divisions-1)
                tree.m_indices.push_back(tree.m_points.size() - (divisions*(divisions-1)+2) + ((divisions-1)*(row+1))  );
              else
                tree.m_indices.push_back(tree.m_points.size() - (divisions*(divisions-1)+2)); //closing with the first point


              //Closing North-pole
              /*tree.indices.push_back(tree.points.size()-1); //north pole point

              tree.indices.push_back(tree.points.size() - ( (divisions*(divisions-1)+2) - (divisions-1)*(row+1) ) -1 );


              if(row<divisions-1)
                tree.indices.push_back(tree.points.size() - ( (divisions*(divisions-1)+2) - ((divisions-1)*(row+2)) ) -1 );
              else
                tree.indices.push_back(tree.points.size() - ( (divisions*(divisions-1)+2) - ((divisions-1)*(row+1)) ) -1 ); //closing with the first point

              */
            }




    }

     //for(unsigned p=0; p< tree.points.size(); ++p)
        //std::cout<<tree.points[p].m_x<<' '<<tree.points[p].m_y<<' '<<tree.points[p].m_z<<'\n';

     return tree;
}

//----------------------------------------------------------------------------------------------------------------
