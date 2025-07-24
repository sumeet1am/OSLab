#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id, at, bt, rt, ct, st, wt, tat, res_t;
    int completed, started;
} Process;

void input(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].id = i;
        p[i].rt = p[i].bt;
        p[i].completed = 0;
        p[i].started = 0;
    }
}

void display(Process p[], int n, float avg_wt, float avg_tat, float avg_rt) {
    printf("\nID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].res_t);
    }
    printf("\nAverage TAT = %.2f", avg_tat);
    printf("\nAverage WT = %.2f", avg_wt);
    printf("\nAverage RT = %.2f\n", avg_rt);
}

void roundRobin(Process p[], int n, int tq) {
    int time = 0, done = 0;
    int queue[100], front = 0, rear = 0, visited[100] = {0};
    float total_tat = 0, total_wt = 0, total_rt = 0;

    // Timeline tracking
    int timeline[200], timeline_index = 0;

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].at > p[j].at) {
                Process t = p[i]; p[i] = p[j]; p[j] = t;
            }

    queue[rear++] = 0;
    visited[0] = 1;

    printf("\nGantt Chart:\n");
    timeline[timeline_index++] = time;

    while (done < n) {
        int idx = queue[front++];

        if (p[idx].started == 0) {
            p[idx].st = time;
            p[idx].res_t = time - p[idx].at;
            p[idx].started = 1;
        }

        int exec = (p[idx].rt >= tq) ? tq : p[idx].rt;
        printf("| P%d ", p[idx].id);
        time += exec;
        timeline[timeline_index++] = time;
        p[idx].rt -= exec;

        // Enqueue new processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !visited[i] && p[i].rt > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].rt > 0) {
            queue[rear++] = idx;
        } else {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
            total_rt += p[idx].res_t;
            done++;
        }

        // Handle idle time
        if (front == rear && done < n) {
            for (int i = 0; i < n; i++) {
                if (p[i].rt > 0) {
                    if (time < p[i].at) {
                        time = p[i].at;
                        timeline[timeline_index++] = time;
                    }
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    printf("|\n");

    // Print timeline below Gantt chart
    for (int i = 0; i < timeline_index; i++) {
        printf("%-5d", timeline[i]);
    }
    printf("\n");

    display(p, n, total_wt / n, total_tat / n, total_rt / n);
}

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];
    input(p, n);
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    roundRobin(p, n, tq);
    return 0;
}
