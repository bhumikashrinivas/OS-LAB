#include<stdio.h>

int main()
{
    int n, bt[20], at[20], tat[20], wt[20], ct[20];
    int i;

    printf("Enter the number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter the arrival time for Process %d: ",i+1);
        scanf("%d",&at[i]);

        printf("Enter the burst time for Process %d: ",i+1);
        scanf("%d",&bt[i]);
    }

    ct[0] = at[0] + bt[0];
    for(i=1;i<n;i++)
    {
        ct[i] = ct[i-1] + bt[i];
    }

    for(i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        printf("Turnaround time for Process %d is %d\n",i+1,tat[i]);
    }

    for(i=0;i<n;i++)
    {
        wt[i] = tat[i] - bt[i];

        if(wt[i] < 0)
            wt[i] = 0;

        printf("Waiting time for Process %d is %d\n",i+1,wt[i]);
    }

    float awt = 0.0;
    for(i=0;i<n;i++)
    {

        awt = awt + wt[i];
    }
    awt = awt / n;


    float atat = 0.0;
    for(i=0;i<n;i++)
    {
        atat = atat + tat[i];
    }
    atat = atat / n;

    printf("Average waiting time : %.2f\n",awt);
    printf("Average turnaround time : %.2f\n",atat);

    return 0;
}
