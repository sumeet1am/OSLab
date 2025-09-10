#include <stdio.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int id, at, bt, rt;         // at=arrival, bt=burst, rt=remaining time
    int st, ct, tat, wt, rt_time, started;
} Process;

void input(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time of P%d: ", p[i].id);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;   // remaining time initially = burst
        p[i].started = 0;
        p[i].rt_time = -1;   // response time not set
    }
}

int findShortest(Process p[], int n, int time) {
    int min_rt = INT_MAX, index = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && p[i].rt > 0 && p[i].rt < min_rt) {
            min_rt = p[i].rt;
            index = i;
        }
    }
    return index;
}

void calculate(Process p[], int n) {
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0, total_rt = 0;

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idx = findShortest(p, n, time);

        if (idx == -1) {  // CPU idle
            time++;
            continue;
        }

        if (p[idx].started == 0) {
            p[idx].st = time;
            p[idx].rt_time = time - p[idx].at; // response time
            p[idx].started = 1;
        }

        // Print exactly like your example: | Pid(1) time|
        printf("| P%d(1) %d", p[idx].id, time + 1);

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_tat += p[idx].tat;
            total_wt  += p[idx].wt;
            total_rt  += p[idx].rt_time;
            completed++;
        }
    }
    printf("|\n");

    printf("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].st,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt_time);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);
}


int main() {
    Process p[MAX];
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    input(p, n);
    calculate(p, n);

    return 0;
}
