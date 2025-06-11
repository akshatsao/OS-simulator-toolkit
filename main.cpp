#include <bits/stdc++.h>
#include "disk_scheduling.h"  
#include "CPU_TEST.h"   
#include "page_replacement.h" 
#include "deadlock_detection.h"
#include "memory_management.h" 
#include "dynamic_semaphore.h" 
using namespace std;

void runCPUScheduling();
void disk_scheduling();
void runPageReplacement();
void runBankersAlgorithm();
void simulateMemoryManagement();
void runSynchronizationSimulation() ;

void showMainMenu() {
    cout << "\n========== OS SIMULATOR ==========\n";
    cout << "1. CPU Scheduling Algorithms\n";
    cout << "2. Disk Scheduling Algorithms\n";
    cout << "3. Page Replacement Algorithms\n";
    cout << "4. Deadlock Detection (Banker's Algorithm)\n";
    cout << "5. Memory Management (Fit Strategies)\n";
    cout << "6. Dynamic Semaphore\n";
    cout << "0. Exit\n";
    cout << "==================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    while (true) {
        showMainMenu();
        cin >> choice;
        switch (choice) {
            case 1: runCPUScheduling(); break;
            case 2: disk_scheduling(); break;
            case 3: runPageReplacement(); break;
            case 4: runBankersAlgorithm(); break;
            case 5: simulateMemoryManagement(); break;
            case 6: runSynchronizationSimulation(); break;
            case 0: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
