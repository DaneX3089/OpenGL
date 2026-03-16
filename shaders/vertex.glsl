#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float time;

uniform mat4 trans;

void main(){
    vec3 pos = aPos;
    pos.x += sin(time * 3.0 + aPos.y * 5) * 0.2;
    pos.y += sin(time * 3.0 + aPos.x * 5) * 0.2;
    gl_Position = trans * vec4(pos, 1.0);
    ourColor = aColor;
}