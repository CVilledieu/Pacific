#include "foundation.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define SHADER_DIR "assests/shader/"

#define VERTEX_FILE "default.vert" 
#define FRAG_FILE "default.frag"


static unsigned int compileShader(const char* shaderName, GLenum shaderType){
    char path[256];
    sprintf(path, "%s%s", SHADER_DIR, shaderName);
    FILE* fp;
    fp = fopen(path, "rb");

    assert(fp != NULL && "Failed to open shader file. Check file paths.");
    
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    char* shadeBuffer = malloc(fileSize + 1);
    fread(shadeBuffer, 1, fileSize, fp);
    shadeBuffer[fileSize] = '\0';
    fclose(fp);

    unsigned int shader = glCreateShader(shaderType);
    const char* shaderSource = shadeBuffer;
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error:: Shader failed to compile. \n Shader path: %s \nShader type: %d \n%s \n", path, shaderType, infoLog);
        free(shadeBuffer);
        exit(1);
    }

    free(shadeBuffer);
    return shader;
}

unsigned int createShaders(void){
    unsigned int vertexShader = compileShader(VERTEX_FILE, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(FRAG_FILE, GL_FRAGMENT_SHADER);

    unsigned int ShaderPID  = glCreateProgram();
    glAttachShader(ShaderPID , vertexShader);
    glAttachShader(ShaderPID, fragmentShader);
    glLinkProgram(ShaderPID );

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return ShaderPID;
}