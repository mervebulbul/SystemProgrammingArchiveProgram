#include "../include/archive.h"  // Include the necessary header file

// Function to extract files from an archive
void extractArchive(const char *inputFilename, const char *outputDirectory, char *filenames) {
    FILE *inputFile = fopen(inputFilename, "r");  // Open the archive file for reading
    if (!inputFile) {
        fprintf(stderr, "Error: Could not open archive file %s\n", inputFilename);
        exit(1);
    }

    char line[256]; // Buffer for reading lines from the archive

    // Loop through each line in the archive file
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char filename[100];
        int permissions;
        long size;
        char content[256];

        // Parse each line to extract filename, permissions, size, and content
        if (sscanf(line, "%*[^|]|%99[^,],%o,%ld|%255[^\n]", filename, &permissions, &size, content) == 4) {

            strcat(filenames, filename); // Add filename to the filenames array

            char outputPath[150];
            snprintf(outputPath, sizeof(outputPath), "%s/%s", outputDirectory, filename); // Generate output path

            FILE *outputFile = fopen(outputPath, "w");  // Open file for writing extracted content
            if (!outputFile) {
                fprintf(stderr, "Error: Could not create file %s\n", filename);
                continue; // Skip to the next iteration if unable to create the file
            }

            fwrite(content, sizeof(char), strlen(content), outputFile); // Write content to the output file

            fclose(outputFile); // Close the output file
            chmod(outputPath, permissions); // Set permissions for the extracted file
            strcat(filenames, ", "); // Add a separator for the filenames
        }
    }

    // Remove the trailing comma and space from the filenames
    if (strlen(filenames) > 0) {
        filenames[strlen(filenames) - 2] = '\0';
    }

    fclose(inputFile); // Close the input archive file
}

// Main function
int main(int argc, char *argv[]) {
    // Check the command-line arguments
    if (argc != 4 || strcmp(argv[1], "-a") != 0) {
        printf("Usage: %s -a archive.sau directory\n", argv[0]);
        return 1;
    }

    const char *inputFilename = argv[2]; // Get the input archive filename
    const char *outputDirectory = argv[3]; // Get the output directory

    char filenames[256] = ""; // Array to store filenames extracted from the archive

    extractArchive(inputFilename, outputDirectory, filenames); // Extract files from the archive

    printf("%s files opened in the %s directory.\n", filenames, outputDirectory); // Print extracted filenames

    return 0;
}

