/* @Author
Kevser Günaydin
150190715
13.01.2021 */

#include <iostream>
#include <fstream>

#include "data_structs.h"

using namespace std;


int main(int count, const char* vector[]){

	if(count!=2){
		cerr<<"./scheduler data_file.txt"<<endl;
		return EXIT_FAILURE;
	}

    ifstream file(vector[1]);
	if(!file.is_open()){
		cerr<<"Can not open file"<<endl;
		return EXIT_FAILURE;	
	}

    Queue data;
    data.init();

	Process process;
    process.next=NULL;
    Subtask subtask;

    //read from file into Queue data	
    while(file >> process.name >> process.priority){
        
        if(file >> process.arrival_time>> process.task_count){
            
            process.priority -= 1;
            int ctr;
            int deadline = process.arrival_time;

            process.task_stack.init();
            for(ctr=0;ctr<process.task_count;ctr++){
                
                file>>subtask.name>>subtask.duration;
                subtask.next=NULL;  
                process.task_stack.push(&subtask);
                deadline+=subtask.duration;
    
            }
    
            process.deadline=deadline;  //add deadline and enqueue process 
            data.queue(&process);
            process.task_stack.close();  //delete buffer stack in each iteration
        }
    }
    
    //close file after getting data into queue
    file.close();
    
    //copy data from the queue to multiqueue
    Process* buffer;
    Subtask* sub_buffer;
    MultiQueue mlq;
    mlq.init();

    while(!data.isEmpty()){
        buffer=data.dequeue();
        mlq.enqueue(buffer);
        delete buffer;
    }

//schedule multiqueue
    int time=0;
    int sp_ctr=0; //special condition
    int lateness=0; //cumulative lateness
    int i=0;
   
    while(!mlq.isEmpty()){

        time=mlq.find_time(time);
        
        if(i!=0)
            sp_ctr=mlq.init_sc(time,sp_ctr);

        buffer=mlq.front(i);
        
        if(i==0 && buffer && buffer->arrival_time <= time){
            sub_buffer=buffer->task_stack.pop();
            time += sub_buffer->duration;
            cout<<buffer->name<<' '<<sub_buffer->name<<endl;
            delete sub_buffer;  //delete arranged space for stack's temp

            if(buffer->task_stack.isEmpty()){
                lateness+=time - buffer->deadline;
                buffer=mlq.dequeue(i);
                buffer->task_stack.close();
                delete buffer;  //delete arranged space for queue's temp
            }
        }
    
        else if(i==1 && sp_ctr < 2){
            sub_buffer=buffer->task_stack.pop();
            time+=sub_buffer->duration;
            sp_ctr++; 
            cout<<buffer->name<<' '<<sub_buffer->name<<endl;
            delete sub_buffer;    //delete arranged space for stack's temp

            if(buffer->task_stack.isEmpty()){
                lateness+=time - buffer->deadline;
                buffer=mlq.dequeue(i);
                buffer->task_stack.close();
                delete buffer;  //delete arranged space for queue's temp
            }
            i=0;
        }
    
        else if( i==2 && sp_ctr == 2){
            sub_buffer=buffer->task_stack.pop();
            time += sub_buffer->duration;
            sp_ctr=0;  
            cout<<buffer->name<<' '<<sub_buffer->name<<endl;
            delete sub_buffer;              //delete arranged space for stack's temp

            if(buffer->task_stack.isEmpty()){
                lateness+=time - buffer->deadline;
                buffer=mlq.dequeue(i);
                buffer->task_stack.close();
                delete buffer;     //delete arranged space for queue's temp
            }
            i=0;
        }
        
        else
            i++;
    }
    
    cout<<"Cumulative Lateness: "<<lateness<<endl;

    return EXIT_SUCCESS;
}

