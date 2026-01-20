#ifndef __ENGINE_SHADERS_H__
#define __ENGINE_SHADERS_H__

// Unlike other engine subsystems, Shader programId is private to shader module.
// Exposing only necessary functions to interact with programID(s).

void ShaderInit(void);

void setProgram(void);

void TerminateShaders(void);



#endif