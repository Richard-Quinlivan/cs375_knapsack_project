#include <iostream>
#include <fstream>

using namespace std;

int knapsack_rec(int values[], int weights[], int capacity, int index, int *** table){
	if(index < 0) return 0;
	if((*table)[index][capacity] != -1) return (*table)[index][capacity];
	if(weights[index] > capacity){
		(*table)[index][capacity] = knapsack_rec(values, weights, capacity, index-1, table);
		return (*table)[index][capacity];
	}
	int with = values[index] + knapsack_rec(values, weights, capacity-weights[index], index-1, table);
	int without = knapsack_rec(values, weights, capacity, index-1, table);
	if(with > without) return with;
	return without;
}

int main(){
	int values [] = {1,2,3};
	int weights [] = {1,1,1};
	int capacity = 2;
	int numItems = 3;
	int *** table;
	(*table) = new int *[numItems];
	for(int i = 0; i < numItems; i++){
		(*table)[i] = new int [capacity+1];
	}
	for(int i = 0; i < numItems; i++){
		for(int j = 0; j < capacity+1; j++){
			(*table)[i][j] = -1;
		}
	}

	for(int i = 0; i < numItems; i++){
		for(int j = 0; j < capacity+1; j++){
			cout << (*table)[i][j] << ", ";
		}
		cout << endl;
	}
	cout << endl;
	int soln = knapsack_rec(values, weights, capacity, numItems-1, table);

	// for(int i = 0; i < numItems; i++){
	// 	for(int j = 0; j < capacity+1; j++){
	// 		cout << (*table)[i][j] << ", ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;

	cout << soln << endl;
}