#include<stdio.h>
int main() {
    int n,i;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int AT[n],BT[n],CT[n],TAT[n],WT[n];
    int pid[n];

    for(i=0;i<n;i++){
        printf("Enter Arrival Time and Burst Time for P%d: ",i+1);
        scanf("%d %d",&AT[i],&BT[i]);
        pid[i]=i+1;
    }



    int completed[n];
    int current_time=0,done=0;
    float totalWT=0,totalTAT=0;

    for(i=0;i<n;i++)
        completed[i]=0;

    while(done<n){
        int minBT=9999,index=-1;

        for(i=0;i<n;i++){
            if(AT[i]<=current_time && completed[i]==0){
                if(BT[i]<minBT){
                    minBT=BT[i];
                    index=i;
                }
            }
        }

        if(index==-1){
            current_time++;
        }
        else{
            CT[index]=current_time+BT[index];
            TAT[index]=CT[index]-AT[index];
            WT[index]=TAT[index]-BT[index];

            completed[index]=1;
            current_time=CT[index];
            done++;

            totalWT+=WT[index];
            totalTAT+=TAT[index];
        }
    }

    printf("\n--- SJF NON PREEMPTIVE ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i],AT[i],BT[i],CT[i],TAT[i],WT[i]);
    }

    printf("Average WT = %.2f\n",totalWT/n);
    printf("Average TAT = %.2f\n",totalTAT/n);


    int RT[n];
    int time=0,completed_count=0;
    float totalWT2=0,totalTAT2=0;

    for(i=0;i<n;i++)
        RT[i]=BT[i];

    while(completed_count<n){
        int minRT=9999,index=-1;

        for(i=0;i<n;i++){
            if(AT[i]<=time && RT[i]>0){
                if(RT[i]<minRT){
                    minRT=RT[i];
                    index=i;
                }
            }
        }

        if(index==-1){
            time++;
            continue;
        }

        RT[index]--;
        time++;

        if(RT[index]==0){
            completed_count++;

            CT[index]=time;
            TAT[index]=CT[index]-AT[index];
            WT[index]=TAT[index]-BT[index];

            totalWT2+=WT[index];
            totalTAT2+=TAT[index];
        }
    }

    printf("\n--- SJF PREEMPTIVE (SRTF) ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i],AT[i],BT[i],CT[i],TAT[i],WT[i]);
    }

    printf("Average WT = %.2f\n",totalWT2/n);
    printf("Average TAT = %.2f\n",totalTAT2/n);

    return 0;
}
