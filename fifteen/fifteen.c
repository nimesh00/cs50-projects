/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;
int blank_tiler;
int blank_tilec;
// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    blank_tiler = d - 1;
    blank_tilec = d - 1;

    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(300000);
        }

        // sleep thread for animation's sake
        usleep(300000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(500000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // giving values to tiles as per the dimensions
    int val = d * d;
    int temp;
    for (int i = 0; i < d; i++)
    {
        for ( int j = 0; j < d; j++)
        {
            val--;
            board[i][j] = val;
            
        }
    }
    if (d == 4)
    {
        temp = board[3][1];
        board[3][1] = board[3][2];
        board[3][2] = temp;
    }
        
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // printing out the board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (i == blank_tiler && j == blank_tilec)
            {
                printf("  _");
            }
            else
            {
                printf("%4d",board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // checking the position and then swapping the values of blank tile and tile
    for (int  i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                if ((i == blank_tiler || i == blank_tiler - 1 || i == blank_tiler + 1) && (j == blank_tilec || j == blank_tilec - 1 || j == blank_tilec + 1)&& !(i == blank_tiler + 1 && j == blank_tilec + 1)&& !(i == blank_tiler - 1 && j == blank_tilec - 1)&& !(i == blank_tiler + 1 && j == blank_tilec - 1)&& !(i == blank_tiler - 1 && j == blank_tilec + 1))
                {
                    board[blank_tiler][blank_tilec] = board[i][j];
                    blank_tiler = i;
                    blank_tilec = j;
                    board[blank_tiler][blank_tilec] = 0;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    int swaps = 0;
    int f = d * d;
    int a[f];
    int k = 0;
    for ( int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            a[k++] = board[i][j]; 
        }
    }
    for (int i = 0; i < f; i++)
    {
        if (a[i] > a[i + 1])
        {
            swaps++;
        }
    }
    if(swaps == 1 && board[d - 1][d - 1] == 0)
    {
        return true;
    }
    return false;
}