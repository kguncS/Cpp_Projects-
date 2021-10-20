/* @Author
Kevser Günaydin
150190715
13.01.2021 */

#include "data_structs.h"

void Stack::init(){
    head=NULL;
}

void Stack::close(){
    Subtask* traverse;
    while(head){
        traverse=head;
        head=head->next;
        delete traverse;
    }
}

void Stack::push(Subtask* in){
  
    Subtask* newtask = new Subtask;
    newtask->name = in->name;
    newtask->duration = in->duration;
    if(isEmpty()){
        newtask->next=NULL;
        head=newtask;
    }
    else{
        newtask->next = head;
        head = newtask;
    }
}

Subtask* Stack::pop(){
    
    Subtask *top=head;
    temp=new Subtask;
    temp->name=top->name;
    temp->duration=top->duration;
    temp->next=NULL;
    head=head->next;
    delete top;
    return temp;
}

bool Stack::isEmpty(){
    return head==NULL;
}

void Queue::init(){
    head=NULL;
    tail=NULL;
}

void Queue::close(){
    Process* traverse;
    while(head){
        traverse=head;
        head=head->next;
        traverse->task_stack.close();
        delete traverse;
    }
}

void Queue::queue(Process* in){
    
    Stack buffer; //buffer is made and initialized to store values in the stack to push them in the right order to the stack in the process
    buffer.init();
    
    Process* newprocess=new Process;
    newprocess->name=in->name;
    newprocess->arrival_time=in->arrival_time;
    newprocess->deadline=in->deadline;
    newprocess->priority=in->priority;
    newprocess->task_count=in->task_count;
    newprocess->next=NULL;
    newprocess->task_stack.init();
    
    while(!in->task_stack.isEmpty()){
        buffer.push(in->task_stack.pop());
        delete in->task_stack.temp;   //after usage allocated space for the stack's temp is deleted 
    }
    
    while(!buffer.isEmpty()){       //push values in the buffer to the newprocess;
        newprocess->task_stack.push(buffer.pop());
        delete buffer.temp;
    }

    if (isEmpty()) //empty queue
    {    
		tail = newprocess;
	    head=tail;
	}
    else{
        tail->next = newprocess;
        tail = newprocess;
    }   
}

Process* Queue::dequeue(){
    Stack buffer;
    buffer.init();
    Process *top=head;
    head=head->next;
    if(head==NULL)
        tail=NULL;

    temp=new Process;
    temp->name=top->name;
    temp->arrival_time=top->arrival_time;
    temp->deadline=top->deadline;
    temp->priority=top->priority;
    temp->task_count=top->task_count;
    temp->next=NULL;
    temp->task_stack.init();

    while(!top->task_stack.isEmpty()){
        buffer.push(top->task_stack.pop());
        delete top->task_stack.temp;    //after usage allocated space for the stack's temp is deleted 
    }
    while(!buffer.isEmpty()){          //push values in the buffer to the temp of the process
        temp->task_stack.push(buffer.pop());
        delete buffer.temp;
    }
    
    delete top;
    return temp;
}

bool Queue::isEmpty(){
    return head==NULL;
}

Process* Queue::front(){
    return head;
}

void MultiQueue::init(){
    int i;
    for(i=0;i<3;i++){
        queues[i].init();
    }
}

void MultiQueue::close(){
    int i;
    for(i=0;i<3;i++){
        queues[i].close();
    }
}

void MultiQueue::enqueue(Process* in){
    queues[in->priority].queue(in);
}

Process* MultiQueue::dequeue(int priority){
   return queues[priority].dequeue();
}

bool MultiQueue::isEmpty(){
    int i;
    for(i=0;i<3;i++){
        if(!queues[i].isEmpty())
            return false;
    }
    return true;
}

Process* MultiQueue::front(int priority){
    return queues[priority].front();
}

//function returns when the next process will be given cpu time
int MultiQueue::find_time(int current_time){
    int i;
    int min;
    //if in the given time there are processes that already arrived
    for(i=0;i<3;i++){
        if(!queues[i].isEmpty() && queues[i].head->arrival_time <= current_time)
            return current_time;
    }
    //give min a value
    for(i=0;i<3;i++){
        if(!queues[i].isEmpty())
            min=queues[i].head->arrival_time;
    }
    //compare next process arrivals of each priority with min
    for(i=0;i<3;i++){
        if(!queues[i].isEmpty() && queues[i].head->arrival_time < min)
            min=queues[i].head->arrival_time;
    }
    return min;
}

//check queues 1 and 2 to initialize special condition
int MultiQueue::init_sc(int time, int ctr){

    if(!queues[1].isEmpty() && !queues[2].isEmpty()){
        if(queues[1].head->arrival_time > time && queues[2].head->arrival_time <= time){
            ctr=2;
        }
        else if( queues[1].head->arrival_time <= time && queues[2].head->arrival_time > time ){
            if(ctr==2)
                ctr=1;
        }
    }
    else if(!queues[1].isEmpty() && queues[2].isEmpty())
        ctr=0;
    else if(queues[1].isEmpty() &&  !queues[2].isEmpty())
        ctr=2;
    else 
        ctr=3;
    
    return ctr;
}