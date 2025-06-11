
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include "disk_scheduling.h"

using namespace std;

void fcfs(vector<int> requests, int head) {
    int total = 0;
    cout << "\n[FCFS] Order: " << head;
    for (int req : requests) {
        total += abs(head - req);
        head = req;
        cout << " -> " << req;
    }
    cout << "\nTotal Head Movement (FCFS): " << total << " cylinders\n";
}

void sstf(vector<int> requests, int head) {
    int total = 0;
    vector<bool> visited(requests.size(), false);
    cout << "\n[SSTF] Order: " << head;

    for (size_t i = 0; i < requests.size(); ++i) {
        int minDist = INT_MAX, idx = -1;
        for (size_t j = 0; j < requests.size(); ++j) {
            if (!visited[j] && abs(head - requests[j]) < minDist) {
                minDist = abs(head - requests[j]);
                idx = j;
            }
        }
        visited[idx] = true;
        total += abs(head - requests[idx]);
        head = requests[idx];
        cout << " -> " << head;
    }
    cout << "\nTotal Head Movement (SSTF): " << total << " cylinders\n";
}

void scan(vector<int> requests, int head, int diskSize, bool right) {
    int total = 0;
    vector<int> left, rightSide;

    if (right) rightSide.push_back(diskSize - 1);
    else left.push_back(0);

    for (int req : requests) {
        if (req < head) left.push_back(req);
        else rightSide.push_back(req);
    }

    sort(left.begin(), left.end());
    sort(rightSide.begin(), rightSide.end());

    cout << "\n[SCAN] Order: " << head;
    if (right) {
        for (int r : rightSide) {
            total += abs(head - r);
            head = r;
            cout << " -> " << head;
        }
        for (int i = left.size() - 1; i >= 0; i--) {
            total += abs(head - left[i]);
            head = left[i];
            cout << " -> " << head;
        }
    } else {
        for (int i = left.size() - 1; i >= 0; i--) {
            total += abs(head - left[i]);
            head = left[i];
            cout << " -> " << head;
        }
        for (int r : rightSide) {
            total += abs(head - r);
            head = r;
            cout << " -> " << head;
        }
    }
    cout << "\nTotal Head Movement (SCAN): " << total << " cylinders\n";
}

void look(vector<int> requests, int head, bool right) {
    int total = 0;
    vector<int> left, rightSide;

    for (int req : requests) {
        if (req < head) left.push_back(req);
        else rightSide.push_back(req);
    }

    sort(left.begin(), left.end());
    sort(rightSide.begin(), rightSide.end());

    cout << "\n[LOOK] Order: " << head;
    if (right) {
        for (int r : rightSide) {
            total += abs(head - r);
            head = r;
            cout << " -> " << head;
        }
        for (int i = left.size() - 1; i >= 0; i--) {
            total += abs(head - left[i]);
            head = left[i];
            cout << " -> " << head;
        }
    } else {
        for (int i = left.size() - 1; i >= 0; i--) {
            total += abs(head - left[i]);
            head = left[i];
            cout << " -> " << head;
        }
        for (int r : rightSide) {
            total += abs(head - r);
            head = r;
            cout << " -> " << head;
        }
    }
    cout << "\nTotal Head Movement (LOOK): " << total << " cylinders\n";
}

// Main entry function to be called from main menu
void disk_scheduling() {
    int n, head, diskSize, direction;
    vector<int> requests;

    cout << "\n=== Disk Scheduling Algorithms ===\n";
    cout << "Enter number of disk requests: ";
    cin >> n;

    cout << "Enter disk requests (cylinder numbers):\n";
    requests.resize(n);
    for (int i = 0; i < n; ++i) cin >> requests[i];

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter disk size (e.g., 200): ";
    cin >> diskSize;

    cout << "Enter direction (1 for right, 0 for left): ";
    cin >> direction;

    fcfs(requests, head);
    sstf(requests, head);
    scan(requests, head, diskSize, direction);
    look(requests, head, direction);
}
