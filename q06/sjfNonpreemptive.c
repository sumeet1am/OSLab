#include <stdio.h>
#define MAX 100

typedef struct {
    int id, at, bt;
    int st, ct, tat, wt, rt;
    int done;
} Process;

void input(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].done = 0;
    }
}

int findNext(Process p[], int n, int time) {
    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (!p[i].done && p[i].at <= time) {
            if (idx == -1 || p[i].bt < p[idx].bt ||
               (p[i].bt == p[idx].bt && p[i].at < p[idx].at)) {
                idx = i;
            }
        }
    }
    return idx;
}

void calculate(Process p[], int n) {
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0, total_rt = 0;

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idx = findNext(p, n, time);

        if (idx == -1) { // no process available, CPU idle
            time++;
            continue;
        }

        p[idx].st = (time < p[idx].at) ? p[idx].at : time;
        p[idx].rt = p[idx].st - p[idx].at;
        p[idx].ct = p[idx].st + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;

        printf("| P%d(%d) %d", p[idx].id, p[idx].bt, p[idx].ct);

        time = p[idx].ct;
        total_tat += p[idx].tat;
        total_wt += p[idx].wt;
        total_rt += p[idx].rt;
        completed++;
    }
    printf("|\n");

    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].st,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage WT  = %.2f", total_wt / n);
    printf("\nAverage RT  = %.2f\n", total_rt / n);
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
