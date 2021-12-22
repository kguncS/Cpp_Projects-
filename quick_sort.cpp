#include <iostream>
#include <bits/stdc++.h>  //vector
#include <cctype> //strcasecmp
#include <random> //used to get rand() integer
#include <ctime> //clock
#include <fstream> //used to create fin and fout file streams

using namespace std;

//swaps two vectors on the array according to their positions
void swap_tweets(vector<string>* arr, int i, int j){ 
    vector<string> buffer = arr[j];
    arr[j] = arr[i];
    arr[i] = buffer;
}

 //for the given mode provides comparison to pivot element and changes the positions of the elements between p and r, then returns the new position of the pivot.
int partition_tweets(vector<string>* arr, int p, int r, string mode){      
    int i, pivot, countryComp, nameComp, unixtimeComp;
    //decide the mode of the quicksort and choose pivot
    if(mode == "randomized"){
        pivot = rand() % (r-p + 1) + p;
        swap_tweets(arr, r, pivot);  //swap pivot with the last element
    }
    pivot = r; //pivot is set to position r for both modes
    i = p - 1; 
    int counter = 0;
    for(int j = p; j < r ; j++){ //iteration ends on the pivot

        //compare the current tweet with the tweet in the pivot position 
        countryComp = strcasecmp(arr[j][5].c_str(), arr[pivot][5].c_str()); //compare country names
        nameComp = strcasecmp(arr[j][3].c_str(), arr[pivot][3].c_str());    //compare artist names
        unixtimeComp = strcasecmp(arr[j][2].c_str(), arr[pivot][2].c_str()); //compare unix times
            
        if(countryComp > 0 || (countryComp == 0 && nameComp > 0) || (countryComp == 0 && nameComp == 0 && unixtimeComp > 0)) continue; //continue if the current tweet exceeds the tweet in the pivot position
        i++;
        swap_tweets(arr, i, j); //if not continued i is incremented and element that is less than pivot positioned on i  
    }
    swap_tweets(arr, ++i, pivot);     //pivot element is moved to arr[i+1] where elements less than it resides before 
    return i;    //return pivot position
}


void quick_sort_tweets(vector<string>* arr, int p, int r, string mode){
    int q;
    if(p < r){                                  //control the end of the calls = 1 element remains       
        q = partition_tweets(arr, p, r, mode);  //select pivot for the given mode
        quick_sort_tweets(arr, p, q-1, mode);   //call quicksort for the two halves of the array that are seperated by the pivot                          
        quick_sort_tweets(arr, q+1, r, mode);    
    }
}

//definitions of reading & printing data to files from an array of Tweets
void read_from_csv(string file_name, vector<string> arr[], int N){
    
    ifstream input_file(file_name); 
    if(!input_file.is_open()) throw runtime_error("Could not open file"); //checks if the file is open for reading

    string line, word;
    getline(input_file, line); //take header before the data
    
    for(int i = 0; i < N && !input_file.eof(); i++){         
        arr[i].clear();
        getline(input_file, line);
        //get the new position of the '\t' character on each iteration 
        size_t pos;   
        while((pos = line.find("\t")) != string::npos){
            word = line.substr(0, pos); //get the word using substr starting from 0th position with length pos
            arr[i].push_back(word);     
            line.erase(0, pos + 1);     //erase pos + 1 characters from the line - including tab
        }        
        arr[i].push_back(line); //push the last word left in line to the tweet vector
    }
    input_file.close();   
}

void write_to_csv(string file_name, vector<string> arr[], int N){

    ofstream output_file(file_name);
    if(!output_file.is_open()) throw runtime_error("Could not open file"); //checks if the file is open for writing

    output_file << "tweet_id	tweet_datetime	tweet_unixtime	artist_name	track_title	country" << endl;
    for(int i = 0; i < N; i++){        
        for(string x : arr[i]) output_file << x << "\t"; //prints the contents of the vector seperated by tab character 
        output_file << endl;
    }
    output_file.close();
}