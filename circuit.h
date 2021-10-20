/* @Author
Student Name: Kevser Günaydın
Student ID : 150190715
Date: 07.12.2020*/

#pragma once
#include "resistor.h"

struct circuit{
resistor *head;
void create();
void add_resistor(char, double);
resistor* search(char);
void remove_resistor(char);
void delete_resistor(char);
void circuit_info();
void clear();
};
