# Scheduler
This project aims to solve the scheduling problem of an experimental operating system using a MultiQueue data structure. In this experimental operating system, a process includes sub tasks which are the individual sub programs that should not be interrupted. Because of this property, when a process has the access to the CPU, it executes one sub task before leaving the CPU free.

A sub task has the following properties:
• Name
• Duration

To finish its execution, a process has to execute all the sub tasks it has with an order. The order is
represented with a Stack structure. When given CPU time, process executes the top sub task of the Stack
and leaves the CPU free. To complete the execution, a process needs to be granted CPU time as much as
number of the sub tasks.

A process has the following properties:
• Name
• Priority
• Arriving Time
• Deadline
• Sub Tasks Stack

A process would be initialized at Arriving Time and would like to finish the execution before the Deadline.
Deadline is calculated with the following formula:

Deadline = Arriving Time + Subtask Duration

Lateness of a process is the amount of time that past from the deadline when a process completes all of
its sub tasks.. It can be calculated with the following formula:

Lateness = Completion Time − Deadline
