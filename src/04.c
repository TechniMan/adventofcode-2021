#include "utils.h"

// `line` to read, `csv` pointer to array (returned), `count` is nmemb
void InterpretLineAsCSV(char * line, int * csv, int count)
{
    csv[0] = atoi(strtok(line, ","));
    for (int idx = 1; idx < count; idx++)
    {
        csv[idx] = atoi(strtok(NULL, ","));
    }
    return;
}

const int CARD_GRID_WIDTH = 5;
const int CARD_GRID_SIZE = CARD_GRID_WIDTH * CARD_GRID_WIDTH;
struct BingoCard
{
    int * called;
    int * grid;
}
typedef card;

card Card()
{
    card c;
    c.called = calloc(CARD_GRID_SIZE, sizeof(int));
    c.grid = calloc(CARD_GRID_SIZE, sizeof(int));
    return c;
}

void PrintCard(card card)
{
    int i = 0;
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++, i++)
        {
            printf("%d:%d ", card.grid[i], card.called[i]);
        }
        printf("\n");
    }
}

// sets the number as called and checks its row and column for a win
// returns 1 if the card has become a winning card, 0 otherwise
int CallNumber(card card, int number)
{
    int x = 0, y = 0, i = 0;
    for (y = 0; y < 5; y++)
    {
        for (x = 0; x < 5; x++, i++)
        {
            if (card.grid[i] == number)
            {
                card.called[i] = 1;
                break;
            }
        }
    }

    // check the row
    int rowScore = 0;
    for (int y2 = 0; y2 < 5; y2++)
    {
        if (card.called[x + (y2 * 5)])
        {
            rowScore++;
        }
    }
    if (rowScore == 5) return 1;

    // check the column
    rowScore = 0;
    for (int x2 = 0; x2 < 5; x2++)
    {
        if (!card.called[x2 + (y * 5)])
        {
            rowScore++;
        }
    }
    if (rowScore == 5) return 1;

    return 0;
}

// adds all uncalled numbers together
int CalculateScore(card card)
{
    int score = 0;
    for (int i = 0; i < 25; i++)
    {
        score += card.called[i] * card.grid[i];
    }
    return score;
}

int main(int argc, char ** args)
{
    // actually output text please
    setbuf(stdout, NULL);
    printf("Initiating Bingo subroutine\n");

    // read file
    printf("Loading data...\n");
    const int LINES = 601;
    char * path = "src/inputs/04.txt";
    char ** values = ReadLinesFromFileAsStrings(path, LINES);

    // read the called numbers
    printf("Processing data...\n");
    int calledNumbersCount = 100; // 99 commas => 100 numbers
    int * calledNumbers = calloc(100, sizeof(int));
    InterpretLineAsCSV(values[0], calledNumbers, calledNumbersCount);

    // read the bingo cards
    // 601 lines minus 1 (first line) divide by 6 => 100 cards
    const int CARDS = 100;
    card * cards = calloc(CARDS, sizeof(card));
    for (int c = 0, v = 1; c < CARDS; c++)
    {
        // skip blank line
        v++;
        // init card
        card card = Card();
        // read 5 lines
        for (int r = 0; r < CARD_GRID_WIDTH; r++, v++)
        {
            char * row = values[v];
            for (int ch = 0, col = 0; ch < 14; ch++, col++)
            {
                char * numStr = calloc(2, sizeof(char));
                memcpy(numStr, row + (ch * sizeof(char)), 2);
                int num = atoi(numStr);
                card.grid[col + (r * CARD_GRID_WIDTH)] = num;
            }
        }

        cards[c] = card;
    }

    // play the game
    printf("Now playing Bingo\n\n");
    for (int n = 0; n < calledNumbersCount; n++)
    {
        for (int c = 0; c < CARDS; c++)
        {
            int win = CallNumber(cards[c], calledNumbers[n]);
            if (win)
            {
                int score = CalculateScore(cards[c]);
                printf("Winning number: %d\nBoard score: %d\nFinal sum: %d\n", calledNumbers[n], score, score * calledNumbers[n]);
                goto end;
            }
        }
    }

    PrintCard(cards[0]);

    // end of bingo
end:
    printf("\nBingo subroutine has concluded\nWe hope you enjoyed your bingo experience today\n B I N G O \n");
    return 0;
}
