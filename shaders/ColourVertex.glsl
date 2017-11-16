#version 400 core

// The Model View Projection Matrix
uniform mat4 MVP;

layout (location=0)in vec3 inVert;
layout (location=1)in vec3 inColour;
out vec3 vertColour;

void main()
{

    // Calculating the vertex position
    gl_Position = MVP*vec4(inVert, 1.0);
    vertColour = inColour;
}
