#include <stdio.h>
#include <limits.h>

typedef struct
{
    int id;
    int et;
    int p;
    int d;

    int r_time;
    int next_r;
    int a_d;

} Task;

// Find task with earliest d
int get_edf_task(Task tasks[], int n)
{
    int min_d = INT_MAX;
    int selected = -1;

    for(int i = 0; i < n; i++)
    {
        if(tasks[i].r_time > 0)
        {
            if(tasks[i].a_d < min_d)
            {
                min_d =
                    tasks[i].a_d;

                selected = i;
            }
        }
    }

    return selected;
}

int main()
{
    int n, total_time;

    printf("Enter Number of Tasks: ");
    scanf("%d", &n);

    Task tasks[n];

    // Input
    for(int i = 0; i < n; i++)
    {
        tasks[i].id = i + 1;

        printf("\nTask %d\n", i + 1);

        printf("Execution Time: ");
        scanf("%d", &tasks[i].et);

        printf("p: ");
        scanf("%d", &tasks[i].p);

        printf("d: ");
        scanf("%d", &tasks[i].d);

        tasks[i].r_time = 0;
        tasks[i].next_r = 0;
        tasks[i].a_d = 0;
    }

    printf("\nEnter Total Simulation Time: ");
    scanf("%d", &total_time);

    printf("\n================================");
    printf("\n Earliest d First (EDF)");
    printf("\n================================");

    printf("\n\nTime\tRunning Task");
    printf("\n-------------------------\n");

    // Simulation
    for(int t = 0; t < total_time; t++)
    {
        // Release tasks pically
        for(int i = 0; i < n; i++)
        {
            if(t == tasks[i].next_r)
            {
                tasks[i].r_time =
                    tasks[i].et;

                tasks[i].a_d =
                    t + tasks[i].d;

                tasks[i].next_r +=
                    tasks[i].p;
            }
        }

        // Select EDF task
        int current = get_edf_task(tasks, n);

        if(current != -1)
        {
            printf("%d\tTask %d\n",
                   t,
                   tasks[current].id);

            tasks[current].r_time--;
        }
        else
        {
            printf("%d\tIdle\n", t);
        }
    }

    return 0;
}
