#include "utils.h"

int * ReadIntsFromFile(char * path, int lines)
{
    FILE * f = fopen(path, "r");
    if (f == NULL)
    {
        printf("Failed to read file %s\n", path);
        return NULL;
    }

    char * buffer = calloc(10, sizeof(char));
    int * result = calloc(lines, sizeof(int));
    for (int l = 0; fgets(buffer, 10, f) != NULL; ++l)
    {
        result[l] = atoi(buffer);
    }

    fclose(f);
    return result;
}

char ** ReadLinesFromFileAsStrings(const char * path, int lines)
{
    FILE * f = fopen(path, "r");
    if (f == NULL)
    {
        printf("Failed to read file %s\n", path);
        return NULL;
    }

    const int BUFFER_SIZE = 15;
    char * buffer = calloc(BUFFER_SIZE, sizeof(char));
    char ** result = calloc(lines, sizeof(char*));
    for (int l = 0; fgets(buffer, BUFFER_SIZE, f) != NULL; ++l)
    {
        result[l] = calloc(BUFFER_SIZE, sizeof(char));
        strcpy(result[l], buffer);
    }

    fclose(f);
    return result;
}
