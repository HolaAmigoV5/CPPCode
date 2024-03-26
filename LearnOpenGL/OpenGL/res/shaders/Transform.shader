#shader vertex
#version 330 core
        
layout(location=0) in vec4 aPos;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoord;

out vec2 v_TexCoord;
out vec3 ourColor;
uniform mat4 transform;

void main()
{
    gl_Position = transform * aPos;
    ourColor = aColor;
    v_TexCoord = aTexCoord;
};

#shader fragment
#version 330 core

out vec4 color;

in vec3 ourColor;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;

void main()
{
    color=mix(texture(u_Texture, v_TexCoord),texture(u_Texture1, v_TexCoord)* vec4(ourColor, 1.0),0.8);
}