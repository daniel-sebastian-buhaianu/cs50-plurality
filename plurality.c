#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9
#define MAX_NAME_LEN 20

// Candidates have name and vote count
typedef struct
{
    char* name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char* name);
void print_winner(void);

int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%i", &voter_count);

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
	char* name;
	name = (char*) malloc(MAX_NAME_LEN + 1);
	printf("Vote: ");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = '\0';

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char* name)
{
	for (int i = 0; i < MAX; i++)
	{
		if (strcmp(candidates[i].name, name) == 0)
		{
			candidates[i].votes++;
			return true;
		}
	}
	return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
	int max_votes = 0;
	for (int i = 0; i < MAX; i++)
	{
		if (candidates[i].votes > max_votes)
		{
			max_votes = candidates[i].votes;
		}
	}
	for (int i = 0; i < MAX; i++)
	{
		if (candidates[i].votes == max_votes)
		{
			printf("%s\n", candidates[i].name);
		}
	}
    return;
}
