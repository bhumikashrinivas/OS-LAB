#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], CT[n], TAT[n], WT[n];
    int type[n], done[n];

    for(int i = 0; i < n; i++) {
        printf("Enter AT, BT and Type (1=System, 2=User) for P%d: ", i+1);
        scanf("%d %d %d", &AT[i], &BT[i], &type[i]);
        done[i] = 0;
    }

    int time = 0;

    for(int count = 0; count < n; count++) {
        int idx = -1, minAT = 9999;

        for(int i = 0; i < n; i++) {
            if(type[i] == 1 && done[i] == 0 && AT[i] < minAT) {
                minAT = AT[i];
                idx = i;
            }
        }

        if(idx != -1) {
            if(time < AT[idx])
                time = AT[idx];

            time += BT[idx];

            CT[idx] = time;
            TAT[idx] = CT[idx] - AT[idx];
            WT[idx] = TAT[idx] - BT[idx];

            done[idx] = 1;
        }
    }

    for(int count = 0; count < n; count++) {
        int idx = -1, minAT = 9999;

        for(int i = 0; i < n; i++) {
            if(type[i] == 2 && done[i] == 0 && AT[i] < minAT) {
                minAT = AT[i];
                idx = i;
            }
        }

        if(idx != -1) {
            if(time < AT[idx])
                time = AT[idx];

            time += BT[idx];

            CT[idx] = time;
            TAT[idx] = CT[idx] - AT[idx];
            WT[idx] = TAT[idx] - BT[idx];

            done[idx] = 1;
        }
    }

    float avgWT = 0, avgTAT = 0;

    for(int i = 0; i < n; i++) {
        avgWT += WT[i];
        avgTAT += TAT[i];
    }

    avgWT /= n;
    avgTAT /= n;

    printf("\nPID\tAT\tBT\tType\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%s\t%d\t%d\t%d\n",
            i+1, AT[i], BT[i],
            (type[i] == 1) ? "SYS" : "USR",
            CT[i], TAT[i], WT[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avgWT);
    printf("Average Turnaround Time = %.2f\n", avgTAT);

    return 0;
}
