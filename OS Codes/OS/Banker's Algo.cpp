#include <bits/stdc++.h>
using namespace std;

const int P = 5; // Number of processes
const int R = 3; // Number of resources

// Calculate the Need matrix
void calNeed(int need[P][R], int maxm[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maxm[i][j] - allot[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int processes[], int avail[], int maxm[][R], int allot[][R], vector<int>& safeSeq) {
    int need[P][R];
    calNeed(need, maxm, allot);

    bool finish[P] = {false}; // Tracks if a process is finished
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    while (safeSeq.size() < P) {
        bool found = false;

        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == R) { // If all resources can be allocated
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[i][k];
                    }
                    safeSeq.push_back(processes[i]);
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false; // No process could be safely executed
        }
    }

    return true;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int avail[] = {3, 3, 2};

    // Maximum R that can be allocated to processes
    int maxm[][R] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};

    // Resources allocated to processes
    int allot[][R] = {{0, 1, 0},
                      {2, 0, 0},
                      {3, 0, 2},
                      {2, 1, 1},
                      {0, 0, 2}};

    // Check if the system is in a safe state or not
    vector<int> safeSeq;
    if (isSafe(processes, avail, maxm, allot, safeSeq)) {
        cout << "The system is in a safe state.\nSafe sequence: ";
        for (int i = 0; i < safeSeq.size(); i++) {
            cout << "P" << safeSeq[i];
            if (i != safeSeq.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "The system is not in a safe state." << endl;
    }

    return 0;
}
