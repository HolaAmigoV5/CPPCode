#shader vertex
#version 330 core
        
layout(location=0) in vec4 aPos;
layout(location=1) in vec2 aTexCoord;

out vec2 v_TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * aPos;
    v_TexCoord = aTexCoord;
};

#shader fragment
#version 330 core

out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;

void main()
{
    color=mix(texture(u_Texture, v_TexCoord),texture(u_Texture1, v_TexCoord),0.8);
}