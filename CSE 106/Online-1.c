#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);

    int* votes = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &votes[i]);

    int count;

    for (int i = 0; i <= (n/2); i++)
    {
        if (votes[i] == 0) continue;
        count = 1;
        for (int j = i+1; j < n; j++)
        {
            if (votes[i] == votes[j])
            {
                votes[j] = 0;
                count++;
            }
        }

        if (count > n/2)
        {
            printf("%d", votes[i]);
            free(votes);
            return 0;
        }
    }

    printf("No Majority Candidate\n");
    free(votes);
    return 0;
}