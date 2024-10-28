#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

typedef struct {
    int id, at, bt, rt, ct, wt, tt;
} Process;

void calculateTimes(Process p[], int n) {
    int t = 0, c = 0, mrt, spi;
    while (c < n) {
        mrt = INT_MAX;
        spi = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= t && p[i].rt < mrt && p[i].rt > 0) {
                mrt = p[i].rt;
                spi = i;
            }
         }
        if (spi == -1) {
            t++;
            continue;
        }
        p[spi].rt--;
        if (p[spi].rt == 0) {
            c++;
            p[spi].ct = t + 1;
            p[spi].tt = p[spi].ct - p[spi].at;
            p[spi].wt = p[spi].tt - p[spi].bt;
        }
        t++;
    }
}

void printProcessDetails(Process p[], int n) {
    float twt = 0, ttt = 0;
    printf("PID\tAT\tBT\tCT\tWT\tTT\n");
    for (int i = 0; i < n; i++) {
        twt += p[i].wt;
        ttt += p[i].tt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tt);
    }
    printf("\nAverage Waiting Time: %.2f\n", twt / n);
    printf("Average Turnaround Time: %.2f\n", ttt / n);
}

int main() {
    Process p[MAX_PROCESSES];
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        p[i].id = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }
    calculateTimes(p, n);
    printProcessDetails(p, n);
    return 0;
}
