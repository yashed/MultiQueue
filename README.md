# Multi-Queue Scheduling Implementation

This code is a simulation of a multilevel queue scheduling algorithm for managing processes in an operating system. The algorithm consists of four queues, each with a different priority level. The first queue (q0) uses round-robin scheduling with a time quantum of 5. The second queue (q1) uses shortest job first (SJF) scheduling, while the third queue (q2) also uses SJF scheduling, but with a higher priority than q1. The fourth queue (q3) uses first-in, first-out (FIFO) scheduling.

The program takes user input to add processes to each of the queues, with the user specifying the burst time for each process. The processes are then sorted according to their burst time in the q1 and q2 queues, and the program then runs the multilevel queue scheduling algorithm until all processes have been executed.

For each process, the program calculates the waiting time and turn-around time, and these values are used to calculate the total waiting time and total turn-around time for all processes. Finally, the program outputs the process ID, waiting time, and turn-around time for each process, as well as the average waiting time and average turn-around time for all processes.
