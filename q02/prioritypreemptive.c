#include <stdio.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int id, at, bt, rt, ct, wt, tat, pr, st, resp;
    int completed;
} Process;

void input(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter AT, BT, Priority (lower = higher priority) for P%d: ", i);
        p[i].id = i;
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt;
        p[i].completed = 0;
        p[i].st = -1;
    }
}

int findHighestPriority(Process p[], int n, int time) {
    int min_pr = INT_MAX, idx = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && p[i].rt > 0 && p[i].pr < min_pr) {
            min_pr = p[i].pr;
            idx = i;
        }
    }
    return idx;
}

void calculate(Process p[], int n) {
    int time = 0, completed = 0, prev = -1;

    printf("\nGantt Chart:\n");
    while (completed < n) {
        int idx = findHighestPriority(p, n, time);
        if (idx != -1) {
            if (p[idx].st == -1)
                p[idx].st = time;

            if (p[idx].bt == p[idx].rt)
                p[idx].resp = time - p[idx].at;

            if (idx != prev)
                printf("| %d P%d ", time, p[idx].id);

            p[idx].rt--;
            time++;

            if (p[idx].rt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].completed = 1;
                completed++;
            }
            prev = idx;
        } else {
            if (prev != -2)
                printf("| %d idle ", time);
            time++;
            prev = -2;
        }
    }
    printf("| %d\n", time);
}

void display(Process p[], int n) {
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\nID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT");
    for (int i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",
            p[i].id, p[i].at, p[i].bt, p[i].pr,
            p[i].ct, p[i].tat, p[i].wt, p[i].resp);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
        total_rt += p[i].resp;
    }

    printf("\n\nAvg WT = %.2f", total_wt / n);
    printf("\nAvg TAT = %.2f", total_tat / n);
    printf("\nAvg RT = %.2f\n", total_rt / n);
}

int main() {
    Process p[MAX];
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    input(p, n);
    calculate(p, n);
    display(p, n);
    return 0;
}
