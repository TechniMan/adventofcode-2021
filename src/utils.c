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

    const int bufSize = 12;
    char * buffer = calloc(bufSize, sizeof(char));
    char ** result = calloc(lines, sizeof(char*));
    for (int l = 0; fgets(buffer, bufSize, f) != NULL; ++l)
    {
        result[l] = calloc(bufSize, sizeof(char));
        strcpy(result[l], buffer);
    }

    fclose(f);
    return result;
}
