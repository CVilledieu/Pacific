/*
    Due to the simplicity of my shaders a few short cuts have been taken.
     - Shader program is only called on init, because nothing should cause the shader program to be unmounted for the duration of the app.
     - Shader only has 1 uniform to be called, so the name of the uniform has been hard coded
*/

#include "foundation.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define SHADER_DIR "assests/shader/"

#define VERTEX_FILE "default.vert" 
#define FRAG_FILE "default.frag"

static unsigned int defaultShdaderID = 0;

//If multiple shaders are needed down the road can add enum parameter to determine which program id to use
unsigned int getUniformAddress(void){
    return glGetUniformLocation(defaultShdaderID, "uView");
}

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



void initShader(void){
    unsigned int vertexShader = compileShader(VERTEX_FILE, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(FRAG_FILE, GL_FRAGMENT_SHADER);

    defaultShdaderID  = glCreateProgram();
    glAttachShader(defaultShdaderID , vertexShader);
    glAttachShader(defaultShdaderID, fragmentShader);
    glLinkProgram(defaultShdaderID );

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Nothing should remove Program, so at the moment its safe to call before rendering process.
    // Also saves processing to call once before rendering instead of each render call
    glUseProgram(defaultShdaderID);
}
