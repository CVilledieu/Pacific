#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// SSBO for per-instance model matrices (computed on CPU)
layout(std430, binding = 0) buffer TransformBuffer {
    mat4 modelMatrices[];
};

out vec3 ourColor;

uniform mat4 uView;

void main(){
    mat4 model = modelMatrices[gl_InstanceID];
    
    gl_Position = uView * model * vec4(aPos, 1.0);
    ourColor = aColor;
}