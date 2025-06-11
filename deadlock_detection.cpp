#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "deadlock_detection.h"
using namespace std;

void displayMatrix(const string& name, const vector<vector<int>>& mat) {
    cout << "\n" << name << " Matrix:\n";
    for (int i = 0; i < mat.size(); ++i) {
        cout << "P" << i << ": ";
        for (int val : mat[i]) cout << setw(3) << val;
        cout << "\n";
    }
}

void displayVector(const string& name, const vector<int>& vec) {
    cout << "\n" << name << ": ";
    for (int val : vec) cout << setw(3) << val;
    cout << "\n";
}

bool isSafe(int n, int m, vector<vector<int>>& alloc, vector<vector<int>>& max, vector<int>& avail) {
    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            need[i][j] = max[i][j] - alloc[i][j];

    displayMatrix("Need", need);

    vector<bool> finish(n, false);
    vector<int> work = avail;
    vector<int> safeSeq;

    for (int count = 0; count < n; ++count) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (int j = 0; j < m; ++j)
                        work[j] += alloc[i][j];
                    safeSeq.push_back(i);
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "\n⚠️ System is NOT in a safe state.\n";
            return false;
        }
    }

    cout << "\n✅ System is in a safe state.\nSafe Sequence: ";
    for (int p : safeSeq)
        cout << "P" << p << " ";
    cout << "\n";
    return true;
}
void runBankersAlgorithm() {
    srand(time(0));
    int n, m, mode;
    cout << "\n=== Banker's Algorithm - Safety Check ===\n";
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<int> avail(m);

    cout << "Choose input mode:\n1. Manual Input\n2. Random Values\nEnter choice: ";
    cin >> mode;

    if (mode == 1) {
        cout << "\nEnter Allocation Matrix:\n";
        for (int i = 0; i < n; ++i) {
            cout << "P" << i << ": ";
            for (int j = 0; j < m; ++j)
                cin >> alloc[i][j];
        }

        cout << "\nEnter Max Matrix:\n";
        for (int i = 0; i < n; ++i) {
            cout << "P" << i << ": ";
            for (int j = 0; j < m; ++j)
                cin >> max[i][j];
        }

        cout << "\nEnter Available Resources: ";
        for (int i = 0; i < m; ++i)
            cin >> avail[i];
    } else {
        // Random generation
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                alloc[i][j] = rand() % 5;

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                max[i][j] = alloc[i][j] + rand() % 5;

        for (int i = 0; i < m; ++i)
            avail[i] = rand() % 6;

        cout << "\nRandomly Generated Data:\n";
    }

    displayMatrix("Allocation", alloc);
    displayMatrix("Max", max);
    displayVector("Available", avail);

    isSafe(n, m, alloc, max, avail);
}
