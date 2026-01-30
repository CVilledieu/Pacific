#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// SSBO for per-instance transforms: vec4(x, y, width, height)
layout(std430, binding = 0) buffer TransformBuffer {
    vec4 transforms[];
};

out vec3 ourColor;

uniform mat4 uView;

void main(){
    vec4 t = transforms[gl_InstanceID];
    
    mat4 model = mat4(
        t.z,  0.0,  0.0,  0.0,   // scale X 
        0.0,  t.w,  0.0,  0.0,   // scale Y 
        0.0,  0.0,  1.0,  0.0,   // scale Z 
        t.x,  t.y,  0.0,  1.0    // translation
    );
    
    gl_Position = uView * model * vec4(aPos, 1.0);
    ourColor = aColor;
}