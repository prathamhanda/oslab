#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int priority; // For priority scheduling
};


// Function to calculate waiting time for SJF Non-Preemptive
void calculateSJFNonPreemptive(vector<Process>& processes) {
    int ct = 0;
    int n = processes.size();
    int cp = 0;

    // Add a completed flag to track finished processes
    vector<bool> completed(n, false);

    // Sort based on arrival time first, then burst time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime || 
               (a.arrivalTime == b.arrivalTime && a.burstTime < b.burstTime);
    });

    while (cp < n) {
        // Find the shortest job available at time ct
        int sj = -1;
        int min_burst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrivalTime <= ct && processes[i].burstTime < min_burst) {
                min_burst = processes[i].burstTime;
                sj = i;
            }
        }

        if (sj != -1) {
            // Execute the selected process
            ct += processes[sj].burstTime;
            processes[sj].turnaroundTime = ct - processes[sj].arrivalTime;
            processes[sj].waitingTime = processes[sj].turnaroundTime - processes[sj].burstTime;
            completed[sj] = true;
            cp++;
        } else {
            // No process is ready, advance time
            ct++;
        }
    }

}

// Function to calculate waiting time for Round Robin


void displayResults(const vector<Process>& processes) {
    cout << "\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime 
             << "\t\t" << p.waitingTime << "\t\t" << p.turnaroundTime << endl;
    }
}

int main() {
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time for process " << (i + 1) << ": ";
        cin >> processes[i].arrivalTime;
        
        cout << "Enter burst time for process " << (i + 1) << ": ";
        cin >> processes[i].burstTime;

        processes[i].id = i + 1; // Assigning ID to each process
    }

    
    calculateSJFNonPreemptive(processes);
        
    displayResults(processes);
    return 0;
}
