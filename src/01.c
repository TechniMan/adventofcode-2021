#include "utils.h"

int main(int argc, char ** args)
{
    setbuf(stdout, NULL);

    int lines = 2001;
    char * path = "src/inputs/01.txt";
    int * values = ReadIntsFromFile(path, lines);

    int individualIncreases = 0, previousValue = values[0];
    for (int idx = 1; idx < lines; ++idx)
    {
        individualIncreases += previousValue < values[idx];
        previousValue = values[idx];
    }
    printf("Individual increases: %d\n", individualIncreases);

    int tripletIncreases = 0;
    previousValue = values[0] + values[1] + values[2];
    for (int idx = 3; idx < lines; ++idx)
    {
        int newValue = values[idx-2] + values[idx-1] + values[idx];
        tripletIncreases += previousValue < newValue;
        previousValue = newValue;
    }
    printf("Triplet increases: %d\n", tripletIncreases);

    return 0;
}
