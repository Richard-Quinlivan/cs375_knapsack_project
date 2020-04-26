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
	output.open("output.csv");
	output << "recursive,dynamic" << endl;
	for(int i = 0; i < SAMPLE_SIZE; i++){
		auto recursive_time = 0;
		auto dynamic_time = 0;
		int cap = 50*(i+1); //we scale a fixed capacity with the size of the problem
		for(int j = 0; j < 50; j++){ //runs 50 times and takes average time
			val_arrays[i] = create_random_array(i+1, 10);
			weight_arrays[i] = create_random_array(i+1, 1);
			int **table;
			table = new int*[i+1]; //table for recursive solution: we have to declare it on the heap
			for(int boring = 0; boring <= i; boring++) table[boring] = new int[cap+1];
			for(int fun = 0; fun <= i; fun++){
				for(int funny = 0; funny < cap+1; funny++){
					table[fun][funny] = -1; // intitialize the table to all -1
				}
			}
			auto start = chrono::high_resolution_clock::now();
			int recursive_soln = knapsack_rec(val_arrays[i], weight_arrays[i], cap, i, table);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
			recursive_time += duration.count(); //gets time for one iteration of recursive
			for(int hilarious = 0; hilarious <= i; hilarious++) delete[] table[hilarious];
			delete[] table;
			start = chrono::high_resolution_clock::now();
			int dynamic_soln = dynamic(val_arrays[i], weight_arrays[i], cap, i+1);
			stop = chrono::high_resolution_clock::now(); // same for dynamic
			duration = chrono::duration_cast<chrono::microseconds>(stop-start);
			dynamic_time += duration.count();
			delete[] val_arrays[i];
			delete[] weight_arrays[i];
		}
		output << recursive_time/50 << "," << dynamic_time/50; //output to CSV
		if(i != SAMPLE_SIZE-1) output << endl;
	}
	output.close();
	return 0;
}
