#include <stdio.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int id, at, bt, rt;
    int st, ct, tat, wt;
    int started;
} Process;

void input(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].id);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].started = 0;
    }
}

int findShortest(Process p[], int n, int time) {
    int idx = -1, min_rt = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && p[i].rt > 0 && p[i].rt < min_rt) {
            min_rt = p[i].rt;
            idx = i;
        }
    }
    return idx;
}

void calculate(Process p[], int n) {
    int time = 0, completed = 0, prev = -1;
    float total_tat = 0, total_wt = 0;

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idx = findShortest(p, n, time);

        if (idx == -1) {
            time++;
            continue;
        }

        if (p[idx].started == 0) {
            p[idx].st = time;
            p[idx].started = 1;
        }

        // Print only on context switch
        if (idx != prev) {
            printf("| P%d ", p[idx].id);
            prev = idx;
        }

        // Execute for 1 unit
        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
            completed++;
        }
    }

    printf("|\n\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].st,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
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
