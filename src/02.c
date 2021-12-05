#include "utils.h"

void InterpretLine(char * str, int * forward, int * depth)
{
    // split
    char * direction = strtok(str, " ");
    int magnitude = atoi(strtok(NULL, " "));

    if (strcmp(direction, "forward") == 0)
    {
        *depth = 0;
        *forward = magnitude;
    }
    else if (strcmp(direction, "down") == 0)
    {
        *depth = magnitude;
        *forward = 0;
    }
    else if (strcmp(direction, "up") == 0)
    {
        *depth = -magnitude;
        *forward = 0;
    }
    else
    {
        printf("Failed to interpret direction: '%s'\n", direction);
    }
    return;
}

int main(int argc, char ** args)
{
    // actually output text please
    setbuf(stdout, NULL);

    int lines = 1000;
    char * path = "src/inputs/02.txt";
    char ** values = ReadLinesFromFileAsStrings(path, lines);

    // solve puzzle
    long x1 = 0, y1 = 0;
    long x2 = 0, y2 = 0, aim = 0;
    int depth = 0;
    int forward = 0;
    for (int l = 0; l < lines; ++l)
    {
        InterpretLine(values[l], &forward, &depth);
        x1 += forward;
        y1 += depth;

        aim += depth;
        x2 += forward;
        y2 += forward * aim;
    }

    printf("%ld * %ld = %ld\n", x1, y1, x1 * y1);
    printf("%ld * %ld = %ld\n", x2, y2, x2 * y2);
    return 0;
}
