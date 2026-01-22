/*
    DevNotes: Shaders

    Shader loading 
    --------------
    Shader names are being hard coded for simplicity and ease of development. A management system will be implemented if needed in the future.
    Need for a management system will be determined based on the number of shaders required by the engine in the future.

    Err handling
    --------------
    Since there are a limited number of shaders currently, error handling for shaders generally ends in program termination.

    Future Improvements
    --------------

*/

// DevNote: Shader names will be hard coded for simplicity and ease of development, but if more shaders are required or added I will consider implementing a more robust shader management system. I will be focusing on getting the basic rendering functionality working without getting bogged down in implementing a more complex system that not needed. Error handling for shader compilation and linking is currently omitted for simplicity. Will be added later. Possible Options: read dir contents to load all shaders in a directory, or implement a shader registry to manage multiple shaders.


#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SHADER_DIR "assests/shader/"

// DevNote: Possible useful struct for future shader management system
// Most shaders would share the same base file names with different extensions for easier management
// With that the base name could be used as an identifier for the shader program
// typedef struct {
//     char name[256];
//     typeSystem; // Something to identify number and types of shaders used in program
//     unsigned int programID;
// } ShaderProgram;
// DevNote: Alternatively, a hash map, dictionary, or array could be used to manage pure programIDs

static unsigned int programID = 0;

// Pieces together full path from file name property and defined shader directory.
// Dynamically allocates memory, so caller is responsible for freeing it.
// Returned string is null-terminated.
static unsigned int CompileShader(const char* shaderName, GLenum shaderType){
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
        exit(EXIT_FAILURE);
    }

    free(shadeBuffer);
    return shader;
}


void ShaderInit(void){
    unsigned int vertexShader = CompileShader("basic.vert", GL_VERTEX_SHADER);
    unsigned int fragmentShader = CompileShader("basic.frag", GL_FRAGMENT_SHADER);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void setProgram(void){
    glUseProgram(programID);
}

void TerminateShaders(void){
    glDeleteProgram(programID);
}