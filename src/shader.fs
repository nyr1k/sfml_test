#version 330 core
out vec4 FragColor;
in vec3 ourColor; 

uniform float time; 

void main() {
    //if blue -> red 
    FragColor = vec4(ourColor, 1.0);
    //if red -> green
    //if green -> blue
    
}