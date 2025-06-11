#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include"memory_management.h"
using namespace std;

struct Block {
    int size;
    bool allocated;
    int processID;
};

void printBlocks(const vector<Block>& memory) {
    cout << "\n==== Memory Blocks ====\n";
    for (size_t i = 0; i < memory.size(); i++) {
        cout << "Block " << i << " | Size: " << memory[i].size << " | ";
        if (memory[i].allocated)
            cout << "Allocated to Process " << memory[i].processID << "\n";
        else
            cout << "Free\n";
    }
    cout << "=======================\n";
}

void printProcesses(const vector<int>& processSizes) {
    cout << "\n==== Process Table ====\n";
    cout << "Process ID | Size\n";
    cout << "---------------------\n";
    for (size_t i = 0; i < processSizes.size(); i++) {
        cout << "    " << (i + 1) << "      | " << processSizes[i] << "\n";
    }
    cout << "=======================\n";
}

void firstFit(vector<Block>& memory, int processSize, int pid) {
    for (auto& block : memory) {
        if (!block.allocated && block.size >= processSize) {
            block.allocated = true;
            block.processID = pid;
            cout << "Process " << pid << " allocated using First Fit\n";
            return;
        }
    }
    cout << "No suitable block found for Process " << pid << " (First Fit)\n";
}

void bestFit(vector<Block>& memory, int processSize, int pid) {
    int bestIdx = -1, minWaste = INT_MAX;
    for (size_t i = 0; i < memory.size(); i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            int waste = memory[i].size - processSize;
            if (waste < minWaste) {
                minWaste = waste;
                bestIdx = i;
            }
        }
    }
    if (bestIdx != -1) {
        memory[bestIdx].allocated = true;
        memory[bestIdx].processID = pid;
        cout << "Process " << pid << " allocated using Best Fit\n";
    } else {
        cout << "No suitable block found for Process " << pid << " (Best Fit)\n";
    }
}

void worstFit(vector<Block>& memory, int processSize, int pid) {
    int worstIdx = -1, maxWaste = -1;
    for (size_t i = 0; i < memory.size(); i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            int waste = memory[i].size - processSize;
            if (waste > maxWaste) {
                maxWaste = waste;
                worstIdx = i;
            }
        }
    }
    if (worstIdx != -1) {
        memory[worstIdx].allocated = true;
        memory[worstIdx].processID = pid;
        cout << "Process " << pid << " allocated using Worst Fit\n";
    } else {
        cout << "No suitable block found for Process " << pid << " (Worst Fit)\n";
    }
}

void simulateMemoryManagement() {
    srand(time(0));

    int nBlocks, nProcesses, choice;
    bool randomInput;

    cout << "========== Memory Management Simulation ==========\n";
    cout << "Choose Input Mode:\n";
    cout << "1. Manual Input\n";
    cout << "2. Randomly Generate Values\n";
    cout << "Enter choice: ";
    cin >> choice;
    randomInput = (choice == 2);

    cout << "\nEnter number of memory blocks: ";
    cin >> nBlocks;
    vector<Block> memory(nBlocks);

    if (randomInput) {
        cout << "Generating block sizes randomly (50 to 200)\n";
        for (int i = 0; i < nBlocks; i++) {
            memory[i].size = 50 + rand() % 151;
            memory[i].allocated = false;
            memory[i].processID = -1;
        }
    } else {
        for (int i = 0; i < nBlocks; i++) {
            cout << "Enter size of block " << i << ": ";
            cin >> memory[i].size;
            memory[i].allocated = false;
            memory[i].processID = -1;
        }
    }

    printBlocks(memory);

    cout << "\nEnter number of processes: ";
    cin >> nProcesses;

    vector<int> processSizes;

    // Generate or input process sizes first
    for (int i = 1; i <= nProcesses; i++) {
        int pSize;
        if (randomInput) {
            pSize = 30 + rand() % 100;
        } else {
            cout << "Enter size of Process " << i << ": ";
            cin >> pSize;
        }
        processSizes.push_back(pSize);
    }

    // Show process value table
    printProcesses(processSizes);

    cout << "\nChoose Allocation Algorithm:\n";
    cout << "1. First Fit\n";
    cout << "2. Best Fit\n";
    cout << "3. Worst Fit\n";
    cout << "4. Run All (First Fit + Best Fit + Worst Fit)\n";
    cout << "Enter choice: ";
    cin >> choice;

    // For "Run All", create copies of the memory and run each algorithm separately
    if (choice == 4) {
        // Copies of memory
        vector<Block> memoryFirstFit = memory;
        vector<Block> memoryBestFit = memory;
        vector<Block> memoryWorstFit = memory;

        // FIRST FIT run
        cout << "\n===== FIRST FIT ALLOCATION =====\n";
        for (int i = 1; i <= nProcesses; i++) {
            cout << "\nProcess " << i << " requesting size: " << processSizes[i-1] << "\n";
            firstFit(memoryFirstFit, processSizes[i-1], i);
            printBlocks(memoryFirstFit);
        }

        // BEST FIT run
        cout << "\n===== BEST FIT ALLOCATION =====\n";
        for (int i = 1; i <= nProcesses; i++) {
            cout << "\nProcess " << i << " requesting size: " << processSizes[i-1] << "\n";
            bestFit(memoryBestFit, processSizes[i-1], i);
            printBlocks(memoryBestFit);
        }

        // WORST FIT run
        cout << "\n===== WORST FIT ALLOCATION =====\n";
        for (int i = 1; i <= nProcesses; i++) {
            cout << "\nProcess " << i << " requesting size: " << processSizes[i-1] << "\n";
            worstFit(memoryWorstFit, processSizes[i-1], i);
            printBlocks(memoryWorstFit);
        }

    } else {
        for (int i = 1; i <= nProcesses; i++) {
            int pSize = processSizes[i - 1];
            cout << "\nProcess " << i << " requesting size: " << pSize << "\n";

            switch (choice) {
                case 1: firstFit(memory, pSize, i); break;
                case 2: bestFit(memory, pSize, i); break;
                case 3: worstFit(memory, pSize, i); break;
                default: cout << "Invalid choice!\n"; return;
            }

            printBlocks(memory);
        }
    }

    cout << "========= Simulation Complete =========\n";
}

