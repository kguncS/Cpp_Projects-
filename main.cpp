#include "functions.cpp"

int main(int argc, const char* argv[]){
    int N = stoi(argv[1]); //size of the array
    //create a dynamic array of vectors that will store the contents of the tweets
    vector<string>* tweets = new vector<string>[N];
    string mode = argv[2]; //mode randomzied or deterministic
    
    clock_t t;

    read_from_csv(argv[3], tweets, N); //read from the source data file into tweets array
    
    t = clock();
    quick_sort_tweets(tweets, 0, N - 1, mode); //call quicksort on the tweets array
    t = clock() - t;
    
    write_to_csv(argv[4], tweets, N); //write to the destination data file from the tweets array
    cout << "Sorted in " << (float(t) / CLOCKS_PER_SEC)*1000 << " milliseconds by using " << mode << " pivot selection." << endl;
    delete [] tweets; 
    return 0;
}
