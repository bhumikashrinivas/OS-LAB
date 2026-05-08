#include <stdio.h>
#include <math.h>
int main()
{
    int n, i;
    float e[20], p[20];
    float ut = 0, u, x;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        printf("\nEnter Execution Time for P%d: ", i + 1);
        scanf("%f", &e[i]);
        printf("Enter Period for P%d: ", i + 1);
        scanf("%f", &p[i]);
    }
    for(i = 0; i < n; i++)
    {
        x = e[i] / p[i];
        ut += x;
    }
    ut=ut*100;
    u = n * (pow(2.0, 1.0 / n) - 1)*100;
    printf("\nTotal Utilization in percentage = %f", ut);
    printf("\nUtilization Bound in percentage = %f", u);
    if(ut <= u)
    {
        printf("\nThe System is Surely Schedulable\n");
    }
    else
    {
        printf("\nSchedulability Cannot Be Guaranteed\n");
    }

    return 0;
}
