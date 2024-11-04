#include <iostream>
using namespace std;
int main()
{
    int bt[20], wt[20], tat[20], ct[20], at[20], i, j, n, temp;
    float wtavg = 0, tatavg = 0;
    cout << "Enter the number of processes: ";
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cout << "Enter Arrival Time for Process " << i << ": ";
        cin >> at[i];
        cout << "Enter Burst Time for Process " << i << ": ";
        cin >> bt[i];
    }
    // Sorting the processes based on burst time (SJF)
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (bt[i] > bt[j])
            {
                // Swap burst time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                // Swap arrival time
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
          }
        }
    }
    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];
    wtavg += wt[0];
    tatavg += tat[0];
    for (i = 1; i < n; i++)
    {
        // Calculate the completion time based on the arrival time and previous completion time
        if (at[i] > ct[i - 1])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i - 1] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }
    cout << "\nPROCESS \tARRIVAL TIME \tBURST TIME \tCOMPLETION TIME \tWAITING TIME \tTURNAROUND TIME\n";
    for (i = 0; i < n; i++)
    {
        cout << "\n\t P" << i << "\t\t " << at[i] << "\t\t " << bt[i] << "\t\t " << ct[i] << "\t\t " << wt[i] << "\t\t " << tat[i];
    }
    cout << "\nAverage Waiting Time -- " << wtavg / n;
    cout << "\nAverage Turnaround Time -- " << tatavg / n;
    return 0;
}

