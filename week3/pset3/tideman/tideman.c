#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
//check if the pair generate the cycle
bool cycleGenerator2(int w, int l);

//print func - dbg
void print_prefMatrix();
void print_pairs();
void print_lockedMatrix();

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }


//    print_prefMatrix(); //print preferences matrix

    add_pairs();

//    print_pairs();  // print pairs - dbg

    sort_pairs();

//    print_pairs();  // print pairs - dbg

    lock_pairs();

//    print_lockedMatrix(); //print locked matrix

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Search for name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // ranks arr vs preferences intersection
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j =  0; j < candidate_count; j++)
        {
            if (!(preferences[i][j] == preferences[j][i]) && !(i == j))
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //
    pair buffer; // buffer for swap

    // sort the candidates table in reversed order
    for (int i = 0; i < pair_count - 1; i++)
    {
        int vMin = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[vMin].winner][pairs[vMin].loser])
            {
                vMin = j;
            }
        }
        if (vMin != i)
        {
            buffer.winner = pairs[i].winner;
            buffer.loser = pairs[i].loser;

            pairs[i].winner = pairs[vMin].winner;
            pairs[i].loser = pairs[vMin].loser;
            pairs[vMin].winner = buffer.winner;
            pairs[vMin].loser = buffer.loser;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //
    if (pair_count > 0)
    {
        locked[pairs[0].winner][pairs[0].loser] = true;
    }
    for (int i = 1; i < pair_count; i++)
    {
        if (!cycleGenerator2(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //
    bool noArrow = false;
    int winnerIdx = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                noArrow = false;
                break;
            }
            noArrow = true;
        }
        if (noArrow)
        {
            winnerIdx = i;
            break;
        }

    }
    printf("\n%s\n", candidates[winnerIdx]);
    return;
}


//check if the pair generate the cycle
bool cycleGenerator2(int w, int l)
{
    // graph theory - directed graph : is initial vertice similar with new one
    // recursion base condition, at least one iteration
    if (l == w)
    {
        return true;
    }
    // Alice -> Bob/(0,1); Charlie -> Alice (2, 0); Bob -> Charlie (1, 2);
    //
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[l][i]) //go through
        {
            if (cycleGenerator2(w, i))
            {
                return true;
            }
        }
    }
    return false;
}


//print preferences matrix
void print_prefMatrix()
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j =  0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
}

// print pairs - dbg
void print_pairs()
{
    for (int i = 0; i < pair_count; i++)
    {
        printf("(%i, %i), ", pairs[i].winner, pairs[i].loser);
    }
    printf("\nnumber of pair(s): %i\n", pair_count);
}

//print locked matrix
void print_lockedMatrix()
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j =  0; j < candidate_count; j++)
        {
            printf("%i ", locked[i][j]);
        }
        printf("\n");
    }
}
