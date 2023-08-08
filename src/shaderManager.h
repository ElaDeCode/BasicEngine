#ifndef _EDC_SHADER_MANAGER_H
#define _EDC_SHADER_MANAGER_H

#include "glad/gl.h"
int createFullShader(unsigned int *shaderProgram, const char *vertPath, const char *fragPath, const char *geoPath);
int attachShaderToProgram(unsigned int shaderProgram, const char *path,
                          GLenum ShaderType);
int compileShader(const char *path, unsigned int shader);

#endif