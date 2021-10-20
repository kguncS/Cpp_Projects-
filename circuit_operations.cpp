/* @Author
Student Name: Kevser Günaydın
Student ID : 150190715
Date: 07.12.2020 */

#include <iostream>
#include <stdlib.h>

using namespace std;

#include "circuit.h"


//constructer
void circuit::create(){
	head=NULL;
}

void circuit::add_resistor(char group, double value){
	
	resistor* node, *traverse, *previous;
	traverse=head;

	node=new resistor;
	node->group=group;
	node->value=value;
	node->next=NULL;
	node->quantity=1;
	
	//1st add to the beginning
	if(!traverse){
		head=node;		
		return;
	}
	//node comes before head
	else if(node->value < head->value){
		node->next=head;
		head=node;
		return;
	}
	//check traverse if node comes after head
	while(traverse){
		previous=traverse;
		traverse=traverse->next;
		if(traverse && (node->value < traverse->value)){
			node->next=traverse;
			previous->next=node;
			return;
		}
	}
	//last node
	previous->next=node;
	return;	
}

void circuit::remove_resistor(char group){
	resistor* traverse=search(group);
	if(traverse->quantity == 1)
		delete_resistor(group);	
	else
		traverse->quantity--;
}

void circuit::circuit_info(){
	resistor* traverse=head;
	resistor* previous;
	int count=traverse->quantity;
	double total_resistance=0;
	while(traverse){
		previous=traverse;
		traverse=traverse->next;
		if(traverse && (previous->value == traverse->value)){
			count += traverse->quantity;
		}
		else{
			cout<<previous->value<<":"<<count<<endl;
			traverse==NULL ? count=0 : count=traverse->quantity;
			
		}
	}
	traverse=head;
	while(traverse){
		total_resistance += (traverse->value / traverse->quantity);
		traverse = traverse->next;
	}
	cout<<"Total resistance="<<total_resistance<<" ohm"<<endl;
	
	
}

void circuit::delete_resistor(char group){
	resistor *traverse, *previous;
	traverse=head;
	//deleting the first node	
	if(traverse->group == group){
		head=head->next;
		delete traverse;
		return;
	}

	//deleting a middle point element
	while(traverse){
		previous=traverse;
		traverse=traverse->next;
		if(traverse && (traverse->group == group)){
			previous->next = traverse->next;
			delete traverse;
			return;
		}
	}
}
void circuit::clear(){
	resistor* ptr;
	while(head){
		ptr=head;
		head=head->next;
		delete ptr;
	}
}
resistor* circuit::search(char group){
	resistor* traverse=head;
	while(traverse){
		if(traverse->group == group){
			break;
		}
		traverse=traverse->next;
	}
	return traverse;
}
