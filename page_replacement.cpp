#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <ctime>
using namespace std;

void printMemory(const vector<int>& memory) {
    for (int frame : memory) {
        if (frame == -1) cout << "- ";
        else cout << frame << " ";
    }
    cout << endl;
}

void FIFO(const vector<int>& pages, int frames) {
    cout << "\n--- FIFO Page Replacement ---\n";
    queue<int> q;
    vector<int> memory(frames, -1);
    int page_faults = 0;

    for (int page : pages) {
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            if (q.size() == frames) {
                int removed = q.front(); q.pop();
                replace(memory.begin(), memory.end(), removed, page);
            } else {
                *find(memory.begin(), memory.end(), -1) = page;
            }
            q.push(page);
            page_faults++;
        }
        printMemory(memory);
    }
    cout << "Total Page Faults: " << page_faults << "\n";
}

void LRU(const vector<int>& pages, int frames) {
    cout << "\n--- LRU Page Replacement ---\n";
    vector<int> memory;
    unordered_map<int, int> recent;
    int page_faults = 0;

    for (int i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            if (memory.size() < frames) {
                memory.push_back(page);
            } else {
                int lru_page = memory[0], lru_index = recent[memory[0]];
                for (int j : memory) {
                    if (recent[j] < lru_index) {
                        lru_page = j;
                        lru_index = recent[j];
                    }
                }
                replace(memory.begin(), memory.end(), lru_page, page);
            }
            page_faults++;
        }
        recent[page] = i;

        vector<int> display(frames, -1);
        copy(memory.begin(), memory.end(), display.begin());
        printMemory(display);
    }
    cout << "Total Page Faults: " << page_faults << "\n";
}

void Optimal(const vector<int>& pages, int frames) {
    cout << "\n--- Optimal Page Replacement ---\n";
    vector<int> memory;
    int page_faults = 0;

    for (int i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            if (memory.size() < frames) {
                memory.push_back(page);
            } else {
                int index_to_replace = -1, farthest = i + 1;
                for (int j = 0; j < memory.size(); ++j) {
                    int next_use = pages.size();
                    for (int k = i + 1; k < pages.size(); ++k) {
                        if (pages[k] == memory[j]) {
                            next_use = k;
                            break;
                        }
                    }
                    if (next_use > farthest) {
                        farthest = next_use;
                        index_to_replace = j;
                    }
                }
                if (index_to_replace == -1) index_to_replace = 0;
                memory[index_to_replace] = page;
            }
            page_faults++;
        }
        vector<int> display(frames, -1);
        copy(memory.begin(), memory.end(), display.begin());
        printMemory(display);
    }
    cout << "Total Page Faults: " << page_faults << "\n";
}

void Clock(const vector<int>& pages, int frames) {
    cout << "\n--- Clock Page Replacement ---\n";
    vector<int> memory(frames, -1);
    vector<bool> use_bit(frames, false);
    int hand = 0, page_faults = 0;

    for (int page : pages) {
        auto it = find(memory.begin(), memory.end(), page);
        if (it == memory.end()) {
            while (use_bit[hand]) {
                use_bit[hand] = false;
                hand = (hand + 1) % frames;
            }
            memory[hand] = page;
            use_bit[hand] = true;
            hand = (hand + 1) % frames;
            page_faults++;
        } else {
            use_bit[it - memory.begin()] = true;
        }
        printMemory(memory);
    }
    cout << "Total Page Faults: " << page_faults << "\n";
}

vector<int> generateRandomPages(int n, int maxPage = 9) {
    vector<int> pages(n);
    for (int i = 0; i < n; ++i)
        pages[i] = rand() % (maxPage + 1);
    return pages;
}

void displayMenu() {
    cout << "\nChoose an algorithm:\n";
    cout << "1. FIFO\n";
    cout << "2. LRU\n";
    cout << "3. Optimal\n";
    cout << "4. Clock\n";
    cout << "5. Run All\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}
void runPageReplacement() {
    srand(time(0));

    int frameCount, refSize, choice;
    vector<int> reference;

    cout << "\n=== Page Replacement Algorithm Simulator ===\n";

    cout << "Enter number of frames: ";
    cin >> frameCount;

    cout << "Enter number of page references: ";
    cin >> refSize;

    cout << "1. Manual input\n2. Randomly generate reference string\nChoose option: ";
    int mode;
    cin >> mode;

    if (mode == 1) {
        reference.resize(refSize);
        cout << "Enter page reference string (space-separated): ";
        for (int i = 0; i < refSize; ++i) cin >> reference[i];
    } else {
        reference = generateRandomPages(refSize);
        cout << "Generated Reference String: ";
        for (int val : reference) cout << val << " ";
        cout << "\n";
    }

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: FIFO(reference, frameCount); break;
            case 2: LRU(reference, frameCount); break;
            case 3: Optimal(reference, frameCount); break;
            case 4: Clock(reference, frameCount); break;
            case 5:
                FIFO(reference, frameCount);
                LRU(reference, frameCount);
                Optimal(reference, frameCount);
                Clock(reference, frameCount);
                break;
            case 0: cout << "Exiting Page Replacement Module...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

