#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// SSBO for per-instance transforms (vec4: x, y, w, h)
layout(std430, binding = 0) buffer TransformBuffer {
    vec4 transforms[];
};

// View/projection matrix uniform
uniform mat4 uView;

out vec3 ourColor;


void main(){
    vec4 t = transforms[gl_InstanceID];
    mat4 model = mat4(
         t.z, 0.0f, 0.0f, 0.0f,
        0.0f,  t.w, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
         t.x,  t.y, 0.0f, 1.0f
    );
    
    gl_Position = uView * model * vec4(aPos, 1.0);
    ourColor = aColor;
}