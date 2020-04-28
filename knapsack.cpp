#include "knapsack.h"
#include <chrono>
#include <type_traits>

using namespace std;

int* create_random_array(int size, int bound){ //populates an array with random values
	int* ret = new int[size];
	for(int i = 0; i < size; i++){
		ret[i] = rand() % 100 + bound;
	}
	return ret;
}

int main(){
	srand(time(NULL)); // sets random
	int* val_arrays[SAMPLE_SIZE];
	int* weight_arrays[SAMPLE_SIZE];
	ofstream output;
	output.open("output_brute.csv");
	output << "bruteforce,recursive,dynamic" << endl;
	for(int i = 0; i < SAMPLE_SIZE; i++){
		auto brute_force_time = 0;
		auto recursive_time = 0;
		auto dynamic_time = 0;
		int cap = 50*(i+1); //we scale a fixed capacity with the size of the problem
		for(int j = 0; j < 1; j++){ //runs a given number times and takes average time
			val_arrays[i] = create_random_array(i+1, 10);
			weight_arrays[i] = create_random_array(i+1, 1);
			auto start = chrono::high_resolution_clock::now();
			int brute_force_soln = brute_force_rec(val_arrays[i], weight_arrays[i], cap, i);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
			brute_force_time += duration.count();
			int **table;
			table = new int*[i+1]; //table for recursive solution: we have to declare it on the heap
			for(int one = 0; one <= i; one++) table[one] = new int[cap+1];
			for(int clear_one = 0; clear_one <= i; clear_one++){
				for(int clear_two = 0; clear_two < cap+1; clear_two++){
					table[clear_one][clear_two] = -1; // intitialize the table to all -1
				}
			}
			start = chrono::high_resolution_clock::now();
			int recursive_soln = knapsack_rec(val_arrays[i], weight_arrays[i], cap, i, table);
			stop = chrono::high_resolution_clock::now();
			duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
			recursive_time += duration.count(); //gets time for one iteration of recursive
			for(int del = 0; del <= i; del++) delete[] table[del];
			delete[] table;
			start = chrono::high_resolution_clock::now();
			int dynamic_soln = dynamic(val_arrays[i], weight_arrays[i], cap, i+1);
			stop = chrono::high_resolution_clock::now(); // same for dynamic
			duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
			dynamic_time += duration.count();
			delete[] val_arrays[i];
			delete[] weight_arrays[i];
		}
		output << brute_force_time/1 << "," << recursive_time/1 << "," << dynamic_time/1; //output average times to CSV: for time constraints this code only does one test per level
		if(i != SAMPLE_SIZE-1) output << endl;
	}
	output.close();
	return 0;
}
