#ifndef _EDC_SHADER_MANAGER_H
#define _EDC_SHADER_MANAGER_H

#include "glad/gl.h"
/**
 * @brief compiles the shader from a source file and links it to the shader
 * program
 *
 * @param shaderProgram is where we want to attach the shader
 * @param path is where the shader located relative to executable
 * @param ShaderType MACRO for shader (type this can be GL_VERTEX_SHADER,
 * GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER)
 * @return int
 */
int createFullShader(unsigned int *shaderProgram, const char *vertPath,
                     const char *fragPath, const char *geoPath);
int attachShaderToProgram(unsigned int shaderProgram, const char *path,
                          GLenum ShaderType);
int compileShader(const char *path, unsigned int shader);

#endif