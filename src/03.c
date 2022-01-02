#include "utils.h"

struct BINARYTREENODE {
    int count;
    struct BINARYTREENODE * zero, * one;
} typedef Tree;

Tree * Node() {
    Tree * t = calloc(1, sizeof(Tree));
    t->count = 0;
    t->zero = NULL;
    t->one = NULL;
    return t;
}

// fill out vlen nodes of tree using val
void insert(Tree * root, char * val, int vlen, int depth) {
    if (depth == vlen) { return; }
    if (val[depth] == '0') {
        if (root->zero == NULL) {
            root->zero = Node();
        }
        root->zero->count++;
        insert(root->zero, val, vlen, depth + 1);
    } else if (val[depth] == '1') {
        if (root->one == NULL) {
            root->one = Node();
        }
        root->one->count++;
        insert(root->one, val, vlen, depth + 1);
    }
    return;
}

void free_tree(Tree * root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->zero);
    free_tree(root->one);
    free(root);
}

int bintoint(char * bin, int len) {
    int i = 0;
    for (int c = len - 1, p = 0; c >= 0; c--, p++) {
        i += (bin[c] == '1') * (int)pow(2.0, (double)p);
    }
    return i;
}

int main(int argc, char ** args)
{
    // actually output text please
    setbuf(stdout, NULL);
    printf("Commencing diagnostics\n");

    // read file
    printf("Loading data...\n");
    const int LINES = 1000;
    char * path = "src/inputs/03.txt";
    char ** values = ReadLinesFromFileAsStrings(path, LINES);

    // count bits
    const int CHARS = 12;
    int * count0s = (int*)calloc(CHARS, sizeof(int));
    int * count1s = (int*)calloc(CHARS, sizeof(int));
    Tree * tree = Node();
    for (int l = 0; l < LINES; l++)
    {
        char * line = values[l];
        for (int c = 0; c < CHARS; c++)
        {
            if (line[c] == '1') count1s[c]++;
            else count0s[c]++;
        }
        // insert line into tree
        insert(tree, line, CHARS, 0);
    }
    printf("Processing data...\n");

    // find most/least common bits
    char * gammaStr = calloc(CHARS, sizeof(char));
    char * epsilonStr = calloc(CHARS, sizeof(char));
    for (int c = 0; c < CHARS; c++)
    {
        if (count0s[c] > count1s[c])
        {
            gammaStr[c] = '0';
            epsilonStr[c] = '1';
        }
        else
        {
            gammaStr[c] = '1';
            epsilonStr[c] = '0';
        }
    }
    printf("\n");

    // interpret to numbers
    int gammaRate = bintoint(gammaStr, CHARS);
    printf("Gamma Rate: %d\n", gammaRate);
    int epsilonRate = bintoint(epsilonStr, CHARS);
    printf("Epsilon Rate: %d\n", epsilonRate);

    printf("Power Consumption: %d\n", gammaRate * epsilonRate);
    printf("\n");

    // find the oxygen generator rating based on the most popular bits
    char * oxygenGeneratorStr = calloc(CHARS, sizeof(char));
    Tree * t = tree;
    for (int depth = 0; depth < CHARS; depth++) {
        if (t->zero && t->one) {
            // if more 0s than 1s
            if (t->zero->count > t->one->count) {
                oxygenGeneratorStr[depth] = '0';
                t = t->zero;
            }
            // 1 wins ties
            else {
                oxygenGeneratorStr[depth] = '1';
                t = t->one;
            }
        } else if (t->zero) {
            oxygenGeneratorStr[depth] = '0';
            t = t->zero;
        } else if (t->one) {
            oxygenGeneratorStr[depth] = '1';
            t = t->one;
        } else {
            printf("Error encountered. Oxygen generator rating so far: %s\n", oxygenGeneratorStr);
        }
    }
    int oxygenGeneratorRating = bintoint(oxygenGeneratorStr, CHARS);
    printf("Oxygen Generator Rating: %d\n", oxygenGeneratorRating);

    // find the CO2 scrubber rating based on the least popular bits
    char * co2ScrubberStr = calloc(CHARS, sizeof(char));
    t = tree;
    for (int depth = 0; depth < CHARS; depth++) {
        if (t->zero && t->one) {
            // if fewer 1s than 0s
            if (t->one->count < t->zero->count) {
                co2ScrubberStr[depth] = '1';
                t = t->one;
            }
            // 0 wins ties
            else {
                co2ScrubberStr[depth] = '0';
                t = t->zero;
            }
        } else if (t->zero) {
            co2ScrubberStr[depth] = '0';
            t = t->zero;
        } else if (t->one) {
            co2ScrubberStr[depth] = '1';
            t = t->one;
        } else {
            printf("Error encountered. CO2 scrubber rating so far: %s\n", co2ScrubberStr);
        }
    }
    int co2ScrubberRating = bintoint(co2ScrubberStr, CHARS);
    printf("CO2 Scrubber Rating: %d\n", co2ScrubberRating);

    printf("Life Support Rating: %d\n", co2ScrubberRating * oxygenGeneratorRating);

    // free alloc'd memory
    //free(epsilonStr);
    //free(gammaStr);
    free_tree(tree);
    return 0;
}
