#shader vertex
#version 330 core
        
layout(location=0) in vec4 aPos;

uniform mat4 transform;


void main()
{
    gl_Position = transform * aPos;
};

#shader fragment
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1.0);
}