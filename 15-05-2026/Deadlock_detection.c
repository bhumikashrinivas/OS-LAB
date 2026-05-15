#include <stdio.h>

int main()
{
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m];
    int avail[m];


    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }


    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    int finish[n];


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
                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > avail[j])
                        break;
                }

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
