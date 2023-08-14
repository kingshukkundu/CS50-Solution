#include <cs50.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// each pair has a winner, loser
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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}


void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // For each pair, check for who is preferred
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void)
{
    // Selection sort
    for (int i = 0; i < pair_count - 1; i++)
    {
        // Keep track of min index, starting with index i
        int max = i;
        int max_support = preferences[pairs[max].winner][pairs[max].loser];

        for (int j = i + 1; j < pair_count; j++)
        {
            // compare pairs[j] with pairs[min]
            int support = preferences[pairs[j].winner][pairs[j].loser];
            if (support > max_support)
            {
                max = j;
                max_support = support;
            }
        }

        // Make swap
        pair temp = pairs[i];
        pairs[i] = pairs[max];
        pairs[max] = temp;
    }
}

bool path_exists_helper(int src, int dst, int visited[])
{
    visited[src] = true;

    // Check direct edge
    if (locked[src][dst])
    {
        return true;
    }

    // Check all edges out of src
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[src][i] && !visited[i] && path_exists_helper(i, dst, visited))
        {
            return true;
        }
    }

    // No path exists
    return false;
}

bool path_exists(int src, int dst)
{
    // Track which nodes visited
    int visited[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }

    return path_exists_helper(src, dst, visited);
}

void lock_pairs(void)
{
    // Add each edge to locked graph if it doesn't create a cycle
    for (int i = 0; i < pair_count; i++)
    {
        if (!path_exists(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

void print_winner(void)
{
    // Check for a winner
    for (int i = 0; i < candidate_count; i++)
    {
        bool winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                winner = false;
            }
        }

        if (winner)
        {
            printf("%s\n", candidates[i]);
        }
    }
}

