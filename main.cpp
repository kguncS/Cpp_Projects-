/* @Author
Student Name: Kevser Günaydın
Student ID : 150190715
Date: 07.12.2020*/

#include <iostream>
#include <fstream>

using namespace std;

#include "circuit.h"
#include "resistor.h"

int main(int count,const char* vector[]){
	
	if(count!=2){
		cerr<<"./main file_name.txt"<<endl;
		exit(1);
	}
	
	ifstream file;
	file.open(vector[1],fstream::in);

	if(!file.is_open()){
		cerr<<"Can not open file"<<endl;
		exit(1);	
	}
	
	circuit Circuit;
	Circuit.create();
	
	char group;
	double value;
	
	file >> group >> value;
	while(!file.eof()){
		if(group=='A' && value==0)
			Circuit.circuit_info();
		else {
			resistor* buffer=Circuit.search(group);
			if(buffer == NULL){
				if(value > 0)
					Circuit.add_resistor(group,value);
				else
					cout<<"NO_RESISTOR"<<endl;
			}
			else{
				if(value > 0)
					buffer->quantity++;
				else
					Circuit.remove_resistor(group);
			}
		}
		file >> group >> value;
	}
	file.close();
	Circuit.clear();
	return 0;	
}
