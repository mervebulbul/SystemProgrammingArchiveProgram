#include "../include/archive.h"  // Include the necessary header file

// Function to create an archive
int createArchive(int argc, char *argv[]) {
    // Check if command line arguments are valid
    if (argc < 5 || strcmp(argv[1], "-b") != 0) {
        fprintf(stderr, "Usage: %s -b file1 file2 ... -o s1.sau\n", argv[0]);
        return 1;
    }

    char *output_filename = "a.sau"; // Default output filename
    int i;

    // Find the output file name in the arguments
    for (i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_filename = argv[i + 1];
            break;
        }
    }

    if (i - 2 > MAX_FILES) {
        fprintf(stderr, "Error: Exceeded maximum file count limit (%d)\n", MAX_FILES);
        return 1;
    }

    FILE *output_file = fopen(output_filename, "wb");  // Open output file
    if (output_file == NULL) {
        fprintf(stderr, "Error: Unable to create output file %s\n", output_filename);
        return 1;
    }

    int organizationSize = 10 + ((i - 3) * 25); // Calculate organization size

    FileInfo fileInfo[MAX_FILES]; // Create FileInfo array
    int fileCount = 0;

    // Loop through input files
    for (int j = 2; j < i; j++) {
        FILE *input_file = fopen(argv[j], "rb"); // Open input file
        if (!input_file) {
            fprintf(stderr, "Error: Could not open file %s\n", argv[j]);
            fclose(output_file);
            return 1;
        }

        // Calculate file size
        fseek(input_file, 0, SEEK_END);
        long file_size = ftell(input_file);
        rewind(input_file);

        if (file_size > MAX_FILE_SIZE) {
            fprintf(stderr, "Error: File %s exceeds maximum size limit\n", argv[j]);
            fclose(input_file);
            fclose(output_file);
            return 1;
        }

        // Save file information
        strcpy(fileInfo[fileCount].filename, argv[j]);
        fileInfo[fileCount].permissions = 0644; // Set default permissions
        fileInfo[fileCount].size = file_size;

        fclose(input_file);
        fileCount++;
    }

    // Write organization information and file contents to the archive
    for (int j = 0; j < fileCount; j++) {
        FILE *file_to_archive = fopen(fileInfo[j].filename, "rb"); // Open file to archive
        if (file_to_archive == NULL) {
            fprintf(stderr, "Error: Could not open file %s\n", fileInfo[j].filename);
            return 1;
        }

        // Write file information to the archive
        fprintf(output_file, "%010ld|%s,%o,%ld|", (long)organizationSize, fileInfo[j].filename, 
                fileInfo[j].permissions, fileInfo[j].size);

        // Write file contents to the archive
        int c;
        while ((c = fgetc(file_to_archive)) != EOF) {
            if (fputc(c, output_file) == EOF) {
                fprintf(stderr, "Error: Could not write to archive file\n");
                fclose(file_to_archive);
                return 1;
            }
        }
        fclose(file_to_archive);
    }

    printf("The files have been merged.\n");
    fclose(output_file);

    return 0;
}

// Main function
int main(int argc, char *argv[]) {
    return createArchive(argc, argv); // Call createArchive function
}


