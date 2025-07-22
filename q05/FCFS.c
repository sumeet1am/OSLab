#include <stdio.h>
#include <stdlib.h>

struct process {
    int id, at, bt, st, ct, tat, wt, rt;
};

void input(struct process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
}

void sortByArrival(struct process p[], int n) {
    struct process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at || (p[i].at == p[j].at && p[i].id > p[j].id)) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void fcfs(struct process p[], int n) {
    int time = 0;
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        p[i].st = time;
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].st - p[i].at;
        time = p[i].ct;
        printf(" P%d |", p[i].id);
    }

    printf("\n%d", p[0].st);
    for (int i = 0; i < n; i++) {
        printf("   %2d", p[i].ct);
    }
}

void display(struct process p[], int n) {
    float total_tat = 0, total_wt = 0, total_rt = 0;
    printf("\n\nID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
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
    sortByArrival(p, n);
    fcfs(p, n);
    display(p, n);
    return 0;
}
