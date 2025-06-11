# OS-simulator-toolkit
This is a C++-based OS simulator that visualizes core operating system concepts. It offers a menu-driven console interface to explore CPU scheduling, memory management, page replacement, disk scheduling, deadlock detection, and thread synchronization.
Project Description
SchedulinAlgozzz is a comprehensive Operating System (OS) Simulator built in C++, designed to demonstrate and visualize core OS concepts through interactive modules. It offers students and learners hands-on experience with various OS algorithms and synchronization mechanisms via a dynamic console interface.

The simulator provides a menu-driven system that allows users to choose and execute multiple real-world OS algorithms such as CPU Scheduling, Memory Management, Page Replacement, Disk Scheduling, Deadlock Detection, and Thread Synchronization.

🎯 Key Features
🔄 CPU Scheduling Algorithms
Simulate FCFS, SJF, Round Robin, and Priority Scheduling with turnaround time and Gantt charts.

💾 Memory Management
Supports First Fit, Best Fit, and Worst Fit allocation strategies with fragmentation reports.

📄 Page Replacement Algorithms
Demonstrate FIFO, LRU, and Optimal page replacement using dynamic page/frame input.

🌀 Disk Scheduling Algorithms
Includes FCFS, SCAN, C-SCAN with real-time head movement simulation and seek time calculation.

🧠 Deadlock Detection (Banker's Algorithm)
Simulate safe/unsafe states with dynamic process/resource matrix input.

🔐 Dynamic Semaphore Module
Solve classical synchronization problems like:

Producer-Consumer Problem

Dining Philosophers Problem
Uses mutexes, condition variables, and threads to simulate multithreading challenges.

📋 User-Friendly CLI Interface
Dynamic inputs, colored output, buffer visualization, and logs where applicable.

🧩 Modular Design
Each algorithm is separated into its own file and executable, allowing for clean development and testing.

🛠️ Technologies Used
Language: C++17

Concurrency: std::thread, std::mutex, std::condition_variable, std::atomic

Compilation: g++ (GCC)

Platform: Windows 10 / Linux Terminal

Optional Frontend: Console-based UI

📚 Learning Outcomes
By using SchedulinAlgozzz, users will gain:

Practical understanding of how core OS algorithms function.

Hands-on experience with multithreaded synchronization.

Insights into resource allocation, CPU utilization, and memory fragmentation.

Experience with modular programming, thread-safe design, and performance visualization.
