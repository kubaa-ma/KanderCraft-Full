#include "../include/folders.h"

 #include <windows.h>
#include <stdio.h>
#include <string.h>


int load_folder_names(char *buffer, int bufferSize) {
    WIN32_FIND_DATAA findData;
    char searchPath[MAX_PATH];
    snprintf(searchPath, MAX_PATH, "%s\\*", PATH_WORLD_FILES);

    HANDLE hFind = FindFirstFileA(searchPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        buffer[0] = '\0';
        return 0;\
    }

    buffer[0] = '\0';
    int count = 0;

    do {
        if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            strcmp(findData.cFileName, ".") != 0 &&
            strcmp(findData.cFileName, "..") != 0) {
            
            strncat(buffer, findData.cFileName, bufferSize - strlen(buffer) - 2);
            strncat(buffer, "\n", bufferSize - strlen(buffer) - 1);

            count++;
        }
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);

    return count;
}