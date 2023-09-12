#ifndef SHADER_H
#define SHADER_H

// void newShader();
// void destroyShader();
int createFullShader(unsigned int *shaderProgram, const char *vertPath,
                     const char *fragPath, const char *geoPath);
int attachShaderToProgram(unsigned int shaderProgram, const char *path,
                          unsigned int SHADER_TYPE);
int compileShader(const char *path, unsigned int shader);

#endif