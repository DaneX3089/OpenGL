#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 ourColor;
out vec2 texCoord;

uniform float time;

uniform mat4 trans;

void main(){
    vec3 pos = aPos;
    pos.x += sin(time * 7.0 + aPos.y * 1) * 0.2;
    pos.y += sin(time * 7.0 + aPos.x * 9) * 0.2;
    gl_Position = trans * vec4(pos, 1.0);
    ourColor = vec3(1.0, 1.0, 1.0) * aColor;
    texCoord = aTex;
}