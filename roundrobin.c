//ROUND ROBBIN

#include <stdio.h>

struct Process {
    int pid; // Process ID
    int burstTime; // Burst Time
    int remainingTime; // Remaining Time
    int waitingTime; // Waiting Time
    int turnaroundTime; // Turnaround Time
    int finishTime; // Finish Time
};

int main() {
    int n, quantum, currentTime = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        processes[i].pid = i + 1;
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].finishTime = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                if (processes[i].remainingTime > quantum) {
                    currentTime += quantum;
                    processes[i].remainingTime -= quantum;
                } else {
                    currentTime += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    processes[i].finishTime = currentTime;
                    processes[i].turnaroundTime = processes[i].finishTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    completed++;
                }
            }
        }
    }

    printf("\nProcess\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burstTime, processes[i].finishTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }

    return 0;
}

// INPUT:-
// 3
// 5
// 3
// 8
// 3