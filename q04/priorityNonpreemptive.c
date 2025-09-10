#include <stdio.h>
#include <limits.h>
#define MAX 100

typedef struct {
    int id, at, bt, pr;
    int st, ct, tat, wt, rt_time, started;
} Process;

void input(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter AT, BT, Priority of P%d: ", p[i].id);
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].started = 0;
    }
}

int findNext(Process p[], int n, int time) {
    int idx = -1, minPr = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (p[i].started == 0 && p[i].at <= time) {
            if (p[i].pr < minPr || 
               (p[i].pr == minPr && p[i].at < p[idx].at)) {
                minPr = p[i].pr;
                idx = i;
            }
        }
    }
    return idx;
}

void calculate(Process p[], int n) {
    int time = 0, completed = 0;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idx = findNext(p, n, time);

        if (idx == -1) { time++; continue; }

        p[idx].st = (time < p[idx].at) ? p[idx].at : time;
        p[idx].rt_time = p[idx].st - p[idx].at;
        p[idx].ct = p[idx].st + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
        p[idx].started = 1;

        printf("| P%d(%d) %d", p[idx].id, p[idx].bt, p[idx].ct);

        sum_tat += p[idx].tat;
        sum_wt  += p[idx].wt;
        sum_rt  += p[idx].rt_time;
        time = p[idx].ct;
        completed++;
    }
    printf("|\n");

    printf("\nPID\tAT\tBT\tPR\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr,
               p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt_time);
    }

    printf("\nAverage TAT: %.2f", sum_tat / n);
    printf("\nAverage WT: %.2f", sum_wt / n);
    printf("\nAverage RT: %.2f\n", sum_rt / n);
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
