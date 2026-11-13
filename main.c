

#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    char *source;
    long file_size;

    // Use the filename supplied on the command line.
    // If no filename is given, use input.c.
    const char *filename = (argc > 1) ? argv[1] : "input.c";

    // Open the source file in read mode
    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    // Move to the end of the file
    if (fseek(fp, 0, SEEK_END) != 0)
    {
        printf("Error: Unable to seek in file\n");
        fclose(fp);
        return 1;
    }

    // Find the file size
    file_size = ftell(fp);

    if (file_size < 0)
    {
        printf("Error: Unable to determine file size\n");
        fclose(fp);
        return 1;
    }

    // Return to the beginning of the file
    if (fseek(fp, 0, SEEK_SET) != 0)
    {
        printf("Error: Unable to seek in file\n");
        fclose(fp);
        return 1;
    }

    // Allocate memory for the source code
    source = malloc((size_t)file_size + 1);

    if (source == NULL)
    {
        printf("Error: Memory allocation failed\n");
        fclose(fp);
        return 1;
    }

    // Read the file contents
    size_t bytes_read = fread(source, 1, (size_t)file_size, fp);

    if (bytes_read != (size_t)file_size)
    {
        printf("Error: Unable to read the complete file\n");

        free(source);
        fclose(fp);

        return 1;
    }

    // Add the null terminator
    source[bytes_read] = '\0';

    fclose(fp);

    printf("Lexical Analyzer\n");
    printf("Source file: %s\n", filename);

    // Analyze the source code
    analyze_source(source);

    // Release allocated memory
    free(source);

    return 0;
}
