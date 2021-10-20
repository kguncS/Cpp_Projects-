/* @Author
Kevser Günaydin
150190715
13.01.2021 */

#pragma once
#include <string>
#include <iostream>
#include<stdlib.h>

using namespace std;

struct Subtask{
    string name;
    int duration;
    Subtask* next;
};

struct Stack{
    Subtask* head;
    void init();
    void close();
    void push(Subtask* in);
    Subtask* pop();
    bool isEmpty();
    Subtask* temp;
};

struct Process{
    string name;
    int arrival_time;
    int deadline;
    int task_count;
    int priority;
    Stack task_stack;
    Process* next;
};

struct Queue{
    Process* head;
    Process* tail;
    void init();
    void close();
    void queue(Process* in);
    Process* dequeue();
    bool isEmpty();
    Process* front();
    Process* temp;
};

struct MultiQueue{
    Queue queues[3];
    void init();
    void close();
    void enqueue(Process* in);
    Process* dequeue(int priority);
    bool isEmpty();
    Process* front(int priority);
    int find_time(int current_time);
    int init_sc(int time, int ctr);
};