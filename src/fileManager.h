#ifndef _EDC_FILE_MANAGER_H
#define _EDC_FILE_MANAGER_H

#define FM_FILE_OPEN_FAIL -1
#define FM_MALLOC_FAIL -2

/**
 * @brief Create a Buffer From File object
 * @param dst is the address of the buffer where we store the contents of the
 * file
 * @param path is the path of the file which we want to open
 * @return value is the lenght of the null terminated buffer
 */
int createBufferFromFile(char **dst, const char *path);

#endif