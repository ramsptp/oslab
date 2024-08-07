#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 20

struct process
{
    int pid, at, bt, prio, ct, ta, wt;
};

void swap(struct process *a, struct process *b)
{
    struct process temp = *a;
    *a = *b;
    *b = temp;
}

void sort_prio(struct process arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].prio > arr[j + 1].prio)
                swap(&arr[j], &arr[j + 1]);
}

void sort_pid(struct process arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].pid > arr[j + 1].pid)
                swap(&arr[j], &arr[j + 1]);
}

int main()
{
    int pid, i, j, min_at = INT_MAX;

    do
    {
        printf("Enter number of processes (upto %d): ", MAX);
        scanf("%d", &pid);
    } while (pid <= 0 || pid > MAX);

    struct process npprio[pid]; // npprio stands for non-preemptive priority

    printf("Enter Process Details: ");
    for (int i = 0; i < pid; i++)
    {
        printf("\nProcess ID: %d", i + 1);
        npprio[i].pid = i + 1;

        printf("\nArrival Time: ");
        scanf("%d", &npprio[i].at);

        printf("Burst Time: ");
        scanf("%d", &npprio[i].bt);

        printf("Priority: ");
        scanf("%d", &npprio[i].prio);

        if (min_at > npprio[i].at)
            min_at = npprio[i].at;
    }

    int current_time = min_at;
    int completed = 0;
    int is_completed[pid];
    for (i = 0; i < pid; i++)
        is_completed[i] = 0;

    float avta = 0, avwt = 0;

    while (completed != pid)
    {
        int idx = -1;
        int highest_priority = INT_MAX;

        for (i = 0; i < pid; i++)
        {
            if (npprio[i].at <= current_time && is_completed[i] == 0)
            {
                if (npprio[i].prio < highest_priority)
                {
                    highest_priority = npprio[i].prio;
                    idx = i;
                }
                if (npprio[i].prio == highest_priority)
                {
                    if (npprio[i].at < npprio[idx].at)
                    {
                        highest_priority = npprio[i].prio;
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            npprio[idx].wt = current_time - npprio[idx].at;
            if (npprio[idx].wt < 0)
                npprio[idx].wt = 0;

            npprio[idx].ct = current_time + npprio[idx].bt;
            npprio[idx].ta = npprio[idx].ct - npprio[idx].at;

            avta += npprio[idx].ta;
            avwt += npprio[idx].wt;

            is_completed[idx] = 1;
            completed++;
            current_time = npprio[idx].ct;
        }
        else
        {
            current_time++;
        }
    }

    sort_pid(npprio, pid);

    printf("\nProcess Table:\n");
    printf("PID\tAT\tBT\tPrio\tCT\tTA\tWT\n");
    for (int i = 0; i < pid; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", npprio[i].pid, npprio[i].at, npprio[i].bt, npprio[i].prio, npprio[i].ct, npprio[i].ta, npprio[i].wt);

    printf("Average TA: %f\n", avta / pid);
    printf("Average WT: %f\n", avwt / pid);

    return 0;
}
