#include "utils.h"

int * ReadIntsFromFile(char * path, int lines)
{
    FILE * f = fopen(path, "r");
    if (f == NULL)
    {
        printf("Failed to read file %s\n", path);
        return NULL;
    }

    char * buff = malloc(10 * sizeof(char));
    int * result = malloc(lines * sizeof(int));
    for (int l = 0; fgets(buff, 10, f) != NULL; ++l)
    {
        result[l] = atoi(buff);
    }

    fclose(f);
    return result;
}
