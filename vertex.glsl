#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;
layout (location = 2) in vec3 normal;

out vec3 FragPos;
out vec3 LightPos;
out vec3 Normal;
out vec3 vColour;

uniform vec3 lightPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
        gl_Position = proj * view * model * vec4(position, 1.0);
        FragPos     = vec3(view * model * vec4(position,1.0));
        LightPos    = vec3(view * vec4(lightPos,1.0));
        Normal      = mat3(transpose(inverse(view * model))) * normal;
        vColour     = colour;
}
