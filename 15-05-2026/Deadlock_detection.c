#include <stdio.h>

int main()
{
    int n, m;

    // n = number of processes
    // m = number of resource types
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m];
    int avail[m];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Request Matrix
    printf("\nEnter Request Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    int finish[n];

    // Initialize finish array
    for(int i = 0; i < n; i++)
    {
        int allocated = 0;

        for(int j = 0; j < m; j++)
        {
            if(alloc[i][j] != 0)
            {
                allocated = 1;
                break;
            }
        }

        if(allocated)
            finish[i] = 0;
        else
            finish[i] = 1;
    }

    int found;

    do
    {
        found = 0;

        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int j;

                // Check if request can be satisfied
                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > avail[j])
                        break;
                }

                // If all requests can be satisfied
                if(j == m)
                {
                    for(int k = 0; k < m; k++)
                    {
                        avail[k] += alloc[i][k];
                    }

                    finish[i] = 1;
                    found = 1;

                    printf("Process P%d executed\n", i);
                }
            }
        }

    } while(found);

    // Check for deadlock
    int deadlock = 0;

    printf("\nDeadlocked Processes: ");

    for(int i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0)
        printf("None");

    printf("\n");

    return 0;
}
