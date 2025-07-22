#include <stdio.h>
#include <stdlib.h>

struct process {
    int id, bt, pr, st, ct, tat, wt, rt;
    int completed;
};

void input(struct process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Burst Time and Priority (lower number = higher priority) for P%d: ", i + 1);
        scanf("%d%d", &p[i].bt, &p[i].pr);
        p[i].completed = 0;
    }
}

int findNext(struct process p[], int n) {
    int min_pr = 9999, idx = -1;
    for (int i = 0; i < n; i++) {
        if (!p[i].completed && p[i].pr < min_pr) {
            min_pr = p[i].pr;
            idx = i;
        }
    }
    return idx;
}

void priorityNonPreemptive(struct process p[], int n) {
    int time = 0;
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        int idx = findNext(p, n);
        p[idx].st = time;
        p[idx].ct = time + p[idx].bt;
        p[idx].tat = p[idx].ct;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].rt = p[idx].st;
        time = p[idx].ct;
        p[idx].completed = 1;
        printf(" P%d |", p[idx].id);
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("   %2d", p[i].ct);
    }
}

void display(struct process p[], int n) {
    float total_tat = 0, total_wt = 0, total_rt = 0;
    printf("\n\nID\tBT\tPR\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].bt, p[i].pr, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
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
    priorityNonPreemptive(p, n);
    display(p, n);
    return 0;
}
