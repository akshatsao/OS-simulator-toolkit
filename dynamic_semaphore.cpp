#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>
#include <random>
#include <atomic>
#include <limits>
#include <memory> // For unique_ptr
#include"dynamic_semaphore.h"

using namespace std;

// Globals for Producer-Consumer
queue<int> buffer;
mutex mtx;
condition_variable not_full, not_empty;
int BUFFER_SIZE;
atomic<bool> stop_flag(false);

// Dining Philosophers
vector<unique_ptr<mutex>> forks;

// Random delay utility
void randomDelay(int min_ms, int max_ms) {
    static thread_local mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(min_ms, max_ms);
    this_thread::sleep_for(chrono::milliseconds(dist(rng)));
}

// Producer function
void producer(int id) {
    int item = 0;
    while (!stop_flag) {
        randomDelay(500, 1500); // Simulate work
        unique_lock<mutex> lock(mtx);

        not_full.wait(lock, [] { return buffer.size() < BUFFER_SIZE || stop_flag; });

        if (stop_flag) break;

        item++;
        buffer.push(item);
        cout << "[Producer " << id << "] Produced item " << item
             << " | Buffer size: " << buffer.size() << "/" << BUFFER_SIZE << endl;

        lock.unlock();
        not_empty.notify_one();
    }
}

// Consumer function
void consumer(int id) {
    while (!stop_flag) {
        randomDelay(700, 1700); // Simulate work
        unique_lock<mutex> lock(mtx);

        not_empty.wait(lock, [] { return !buffer.empty() || stop_flag; });

        if (stop_flag && buffer.empty()) break;

        if (!buffer.empty()) {
            int item = buffer.front();
            buffer.pop();
            cout << "[Consumer " << id << "] Consumed item " << item
                 << " | Buffer size: " << buffer.size() << "/" << BUFFER_SIZE << endl;
        }

        lock.unlock();
        not_full.notify_one();
    }
}

// Philosopher function
void philosopher(int id, int num_philosophers) {
    int left = id;
    int right = (id + 1) % num_philosophers;

    while (!stop_flag) {
        cout << "[Philosopher " << id << "] is THINKING." << endl;
        randomDelay(1000, 2000);

        if (stop_flag) break;

        // Lock forks in a fixed order to avoid deadlock
        if (left < right) {
            forks[left]->lock();
            forks[right]->lock();
        } else {
            forks[right]->lock();
            forks[left]->lock();
        }

        if (stop_flag) {
            forks[left]->unlock();
            forks[right]->unlock();
            break;
        }

        cout << "[Philosopher " << id << "] is EATING with forks "
             << left << " & " << right << "." << endl;
        randomDelay(1500, 2500);

        forks[left]->unlock();
        forks[right]->unlock();
        cout << "[Philosopher " << id << "] finished EATING and released forks." << endl;
    }
}

// Main simulation function
void runSynchronizationSimulation() {
    while (true) {
        cout << "\n========== Synchronization Simulation ==========\n";
        cout << "1. Producer-Consumer Problem\n";
        cout << "2. Dining Philosophers Problem\n";
        cout << "3. Exit to Main Menu\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 3) {
            cout << "Returning to main menu...\n";
            break;
        }

        stop_flag = false;

        if (choice == 1) {
            int num_producers, num_consumers;
            cout << "Enter number of producers: ";
            cin >> num_producers;
            cout << "Enter number of consumers: ";
            cin >> num_consumers;
            cout << "Enter buffer size: ";
            cin >> BUFFER_SIZE;

            buffer = queue<int>(); // Reset buffer

            vector<thread> producers, consumers;

            for (int i = 0; i < num_producers; i++)
                producers.emplace_back(producer, i + 1);
            for (int i = 0; i < num_consumers; i++)
                consumers.emplace_back(consumer, i + 1);

            cout << "\nSimulation running... Press ENTER to stop.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline
            cin.get();

            stop_flag = true;
            not_full.notify_all();
            not_empty.notify_all();

            for (auto& t : producers) t.join();
            for (auto& t : consumers) t.join();

            cout << "\n✅ Producer-Consumer Simulation Ended.\n";

        } else if (choice == 2) {
            int num_philosophers;
            cout << "Enter number of philosophers: ";
            cin >> num_philosophers;

            forks.clear();
            for (int i = 0; i < num_philosophers; ++i)
                forks.emplace_back(make_unique<mutex>());

            vector<thread> philosophers;
            for (int i = 0; i < num_philosophers; i++)
                philosophers.emplace_back(philosopher, i, num_philosophers);

            cout << "\nSimulation running... Press ENTER to stop.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            stop_flag = true;

            for (auto& t : philosophers) t.join();

            cout << "\n✅ Dining Philosophers Simulation Ended.\n";
        } else {
            cout << "❌ Invalid choice! Please try again.\n";
        }
    }
}
