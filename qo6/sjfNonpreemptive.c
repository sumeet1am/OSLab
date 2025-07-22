#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process {
    int id, at, bt, st, ct, tat, wt, rt, done;
};

void input(struct process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        p[i].done = 0;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
}

int findNextProcess(struct process p[], int n, int time) {
    int min_bt = INT_MAX, idx = -1;
    for (int i = 0; i < n; i++) {
        if (!p[i].done && p[i].at <= time && p[i].bt < min_bt) {
            min_bt = p[i].bt;
            idx = i;
        }
    }
    return idx;
}

void sjf(struct process p[], int n) {
    int completed = 0, time = 0;
    printf("\nGantt Chart:\n|");

    while (completed < n) {
        int idx = findNextProcess(p, n, time);

        if (idx == -1) {
            time++; // CPU idle
        } else {
            p[idx].st = time;
            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].st - p[idx].at;
            time = p[idx].ct;
            p[idx].done = 1;
            completed++;
            printf(" P%d |", p[idx].id);
        }
    }

    // Print Gantt chart time labels
    printf("\n");
    time = 0;
    for (int i = 0; i < n; i++) p[i].done = 0; // reset for label printing
    completed = 0;
    time = 0;
    printf("%d", time);
    while (completed < n) {
        int idx = findNextProcess(p, n, time);
        if (idx == -1) {
            time++;
        } else {
            printf("   %2d", time + p[idx].bt);
            time += p[idx].bt;
            p[idx].done = 1;
            completed++;
        }
    }
}

void display(struct process p[], int n) {
    float total_tat = 0, total_wt = 0, total_rt = 0;
    printf("\n\nID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt,
               p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        total_rt += p[i].rt;
    }
    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage WT  = %.2f", total_wt / n);
    printf("\nAverage RT  = %.2f\n", total_rt / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    input(p, n);
    sjf(p, n);
    display(p, n);
    return 0;
}
