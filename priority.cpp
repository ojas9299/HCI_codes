#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

const int N = 100005;

struct process {
    int priority;
    int id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int finishing_time;
    int turn_around_time;
};

int n;
process P[N];

// Comparator function to sort processes based on their arrival time and priority
bool operator<(process A, process B) {
    if (A.arrival_time == B.arrival_time) {
        return A.priority > B.priority; // Higher priority (lower number) comes first
    }
    return A.arrival_time < B.arrival_time; // Sort by arrival time if priority is same
}

void Priority() {
    sort(P, P + n); // Sort processes by arrival time and priority
    double total_waiting_time = 0.0;
    double total_turn_around_time = 0.0;

    for (int i = 0; i < n; i++) {
        P[i].finishing_time = (i == 0 ? P[i].arrival_time : max(P[i].arrival_time, P[i - 1].finishing_time)) + P[i].burst_time;
        P[i].turn_around_time = P[i].finishing_time - P[i].arrival_time;
        P[i].waiting_time = P[i].turn_around_time - P[i].burst_time;

        total_waiting_time += P[i].waiting_time;
        total_turn_around_time += P[i].turn_around_time;
    }

    cout << fixed << setprecision(2);
    cout << "ID\tBurst Time\tArrival Time\tPriority\tWT\tCT\tTAT\n";
    for (int i = 0; i < n; i++) {
        cout << P[i].id << "\t" << P[i].burst_time << "\t\t" << P[i].arrival_time << "\t\t" << P[i].priority << "\t\t"
             << P[i].waiting_time << "\t" << P[i].finishing_time << "\t" << P[i].turn_around_time << "\n";
    }

    cout << "Average Waiting Time: " << (total_waiting_time / n) << "\n";
    cout << "Average Turn Around Time: " << (total_turn_around_time / n) << "\n";
}

int main() {
    cout << "Number of Processes: ";
    cin >> n;

    cout << "Process Ids:\n";
    for (int i = 0; i < n; i++) {
        cin >> P[i].id;
    }

    cout << "Process Burst Times:\n";
    for (int i = 0; i < n; i++) {
        cin >> P[i].burst_time;
    }

    cout << "Process Arrival Times:\n";
    for (int i = 0; i < n; i++) {
        cin >> P[i].arrival_time;
    }

    cout << "Process Priorities:\n";
    for (int i = 0; i < n; i++) {
        cin >> P[i].priority;
    }

    Priority();

    return 0;
}




