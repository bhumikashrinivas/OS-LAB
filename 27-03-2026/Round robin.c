#include <stdio.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], RT[n];
    int CT[n], TAT[n], WT[n];

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);


    for(int i = 0; i < n; i++) {
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &AT[i], &BT[i]);
        RT[i] = BT[i];
    }

    int time = 0, done = 0;

    while(done < n) {
        int executed = 0;

        for(int i = 0; i < n; i++) {
            if(AT[i] <= time && RT[i] > 0) {

                executed = 1;

                if(RT[i] > tq) {
                    time += tq;
                    RT[i] -= tq;
                } else {
                    time += RT[i];
                    RT[i] = 0;

                    CT[i] = time;
                    TAT[i] = CT[i] - AT[i];
                    WT[i] = TAT[i] - BT[i];

                    done++;
                }
            }
        }

        if(executed == 0) {
            time++;
        }
    }

    float avgWT = 0, avgTAT = 0;

    for(int i = 0; i < n; i++) {
        avgWT += WT[i];
        avgTAT += TAT[i];
    }

    avgWT /= n;
    avgTAT /= n;


    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
            i+1, AT[i], BT[i],
            CT[i], TAT[i], WT[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avgWT);
    printf("Average Turnaround Time = %.2f\n", avgTAT);

    return 0;
}
