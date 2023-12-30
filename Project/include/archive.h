#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_FILES 32
#define MAX_FILE_SIZE 200000000 // Byte cinsinden 200 MB -> 200 * 1024 * 1024

typedef struct {
    char filename[100];
    int permissions;
    long size;
} FileInfo;

// Function declarations
int createArchive(int argc, char *argv[]);
void extractArchive(const char *inputFilename, const char *outputDirectory, char *filenames);

#endif /* ARCHIVE_H */

