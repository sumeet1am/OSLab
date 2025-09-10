#include <stdio.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int id, at, bt, rt;          // arrival, burst, remaining
    int st, ct, tat, wt, rt_time, started;
} Process;

void input(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time of P%d: ", p[i].id);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].started = 0;
        p[i].rt_time = -1;
    }
}

void calculate(Process p[], int n, int tq) {
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0, total_rt = 0;
    int queue[MAX], front = 0, rear = 0;
    int inQueue[MAX] = {0};

    printf("\nGantt Chart:\n");

    // push first arrivals
    while (1) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !inQueue[i] && p[i].rt > 0) {
                queue[rear++] = i;
                inQueue[i] = 1;
                found = 1;
            }
        }
        if (found || rear > front) break;
        time++;
    }

    while (completed < n) {
        if (front == rear) { // CPU idle
            time++;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && !inQueue[i] && p[i].rt > 0) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++]; // dequeue

        if (p[idx].started == 0) {
            p[idx].st = time;
            p[idx].rt_time = time - p[idx].at;
            p[idx].started = 1;
        }

        int exec_time = (p[idx].rt < tq) ? p[idx].rt : tq;

        // compact Gantt chart: | Pid(exec) endTime|
        printf("| P%d(%d) %d", p[idx].id, exec_time, time + exec_time);

        time += exec_time;
        p[idx].rt -= exec_time;

        // check new arrivals
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !inQueue[i] && p[i].rt > 0) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_tat += p[idx].tat;
            total_wt  += p[idx].wt;
            total_rt  += p[idx].rt_time;
            completed++;
        } else {
            queue[rear++] = idx; // requeue
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
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    input(p, n);

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    calculate(p, n, tq);

    return 0;
}
