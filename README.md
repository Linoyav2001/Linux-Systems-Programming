# Linux Systems Programming & IPC

## Overview
A collection of C programs demonstrating core Operating System concepts, Inter-Process Communication (IPC), and concurrency control in a Linux/POSIX environment. These projects showcase low-level system calls, process management, and synchronization mechanisms.

## Projects Included

### 1. Mini Linux Shell (`/Mini-Shell`)
A custom lightweight Unix shell implementation.
* **Features:** Process creation (`fork`, `wait`), dynamic `$PATH` variable resolution, string parsing, and command execution (`execv`).

### 2. Process Synchronization (`/IPC-Semaphores`)
A concurrency controller that strictly synchronizes the output of 5 independent child processes.
* **Features:** System V Semaphores, avoiding race conditions during concurrent execution, and strict sequential ordering across separate processes.

### 3. Concurrent Shared Memory (`/Shared-Memory-Mutex`)
A program demonstrating safe concurrent writes by 100 child processes to a shared memory segment.
* **Features:** Shared Memory allocation (`shmget`, `shmat`), Critical Section protection using a binary semaphore (Mutex), and atomic operations.

## Tech Stack
* **Language:** C
* **Environment:** Linux / POSIX
* **Key OS Concepts:** Multiprocessing, Synchronization, Inter-Process Communication (IPC), Memory Management.
* **Key System Calls:** `<sys/ipc.h>`, `<sys/sem.h>`, `<sys/shm.h>`, `<sys/wait.h>`, `<unistd.h>`
