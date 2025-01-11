#include <cs50.h>
#include <stdio.h>

typedef struct
{
    string name;
    int votes;
}candidate;

int main(void)
{
    const int num_candidates = 3;
    candidate candidates[num_candidates];

    candidates[0].name = "Carter";
    candidates[0].votes = 10;

    candidates[1].name = "Yuliia";
    candidates[1].votes = 12;

    candidates[2].name = "Inno";
    candidates[2].votes = 7;

    int highest_votes = 0;
    int highest_name;

    for (int i = 0; i < num_candidates; i++)
    {
        if (candidates[i].votes > highest_votes)
        {
            highest_votes = candidates[i].votes;
            highest_name = i;
        }
    }

    printf("%i\n", highest_votes);

    printf("%s\n", candidates[highest_name].name);
}
