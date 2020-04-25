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
	if(with > without)(*table)[index][capacity] = with;
	else (*table)[index][capacity] = without;
	return (*table)[index][capacity];
}

int main(){
	int values [] = {1,2,3,4,5};
	int weights [] = {1,1,2,2,3};
	int capacity = 4;
	int numItems = 5;
	int *** table;
	int ** t;
	table = &t;
	(*table) = new int *[numItems];
	for(int i = 0; i < numItems; i++){
		(*table)[i] = new int[capacity+1];
		/* table is of size [numItems][capacity+1] so that it can account for all states of the problem.
		the table's first index is the number of the item that you are deciding on, the second index is the amount
		of capacity left in the knapsack, these together are unique to each state and cover all possible states */
	}
	for(int i = 0; i < numItems; i++){
		for(int j = 0; j < capacity+1; j++){
			(*table)[i][j] = -1;
		}
	}

	int soln = knapsack_rec(values, weights, capacity, numItems-1, table);



	cout << soln << endl;
}