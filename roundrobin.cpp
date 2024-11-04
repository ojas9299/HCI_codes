#include <bits/stdc++.h>
#include <queue>
#include <iomanip>
#include <cstring>

using namespace std;

struct process {
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnTime;
    int waitingTime;
    int startTime;
};

int main() {
    int n, tq;
    struct process p[50];
    float avgWaiting, avgTurn, avgResponseTime;
    int totalTurn = 0;
    int totalWaiting = 0, index;
    int burstArr[50];
    
    cout << setprecision(2) << fixed;
    
    cout << "Enter the number of processes: ";
    cin >> n;
    
    cout << "Enter time quantum of CPU: ";
    cin >> tq;

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrivalTime;
        
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p[i].burstTime;
        burstArr[i] = p[i].burstTime;
    }

    queue<int> q;
    int currentTime = 0;
    int completed = 0;
    int mark[100];
    
    memset(mark, 0, sizeof(mark));
    mark[0] = 1;
    
    q.push(0);

    while (completed != n) {
        index = q.front();
        q.pop();

        if (burstArr[index] == p[index].burstTime) {
            p[index].startTime = max(currentTime, p[index].arrivalTime);
            currentTime = p[index].startTime;
        }

        if (burstArr[index] > tq) {
            burstArr[index] -= tq;
            currentTime += tq;
        } else {
            currentTime += burstArr[index];
            p[index].completionTime = currentTime;
            p[index].turnTime = p[index].completionTime - p[index].arrivalTime;
            p[index].waitingTime = p[index].turnTime - p[index].burstTime;

            totalWaiting += p[index].waitingTime;
            totalTurn += p[index].turnTime;

            completed++;
            burstArr[index] = 0;
        }

        // Add new processes to the queue
        for (int i = 1; i < n; i++) {
            if (burstArr[i] > 0 && p[i].arrivalTime <= currentTime && mark[i] == 0) {
                mark[i] = 1;
                q.push(i);
            }
        }

        if (burstArr[index] > 0) {
            q.push(index);
        }

        if (q.empty()) {
            for (int i = 1; i < n; i++) {
                if (burstArr[i] > 0) {
                    mark[i] = 1;
                    q.push(i);
                    break;
                }
            }
        }
    }

    avgWaiting = (float)totalWaiting / n;
    avgTurn = (float)totalTurn / n;

    // Calculate Average Response Time
    int totalArrivalTime = 0;
    for (int i = 0; i < n; i++) {
        totalArrivalTime += p[i].arrivalTime;
    }
    avgResponseTime = (float)totalArrivalTime / n;

    cout << endl;
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << p[i].arrivalTime << "\t\t" << p[i].burstTime << "\t\t"
             << p[i].completionTime << "\t\t" << p[i].turnTime << "\t\t" << p[i].waitingTime << "\t\t"
             << p[i].arrivalTime << endl;
    }

    cout << "Average Waiting Time = " << avgWaiting << endl;
    cout << "Average Turnaround Time = " << avgTurn << endl;
    cout << "Average Response Time = " << avgResponseTime << endl;

    return 0;
}

