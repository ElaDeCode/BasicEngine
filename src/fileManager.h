#ifndef _EDC_FILE_MANAGER_H
#define _EDC_FILE_MANAGER_H

/**
 * @brief Create a Buffer From File object
 * @param dst is the address of the buffer where we store the contents of the
 * file
 * @param path is the path of the file which we want to open
 * @return value is the lenght of the null terminated buffer
 */
int createBufferFromFile(char **dst, const char *path);

#endif