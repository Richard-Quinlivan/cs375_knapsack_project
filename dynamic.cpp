#include <iostream>

#include "knapsack.h"

//THIS IS BASICALLY JUST THE GEEKS4GEEKS, TODO: RYAN IMPLEMENTS OWN VERSION

using namespace std;

int max(int a, int b){return (a > b) ? a : b;}

int dynamic(int values[], int weights[], int capacity, int n){
	int store[n+1][capacity+1];
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= capacity; j++){
			if(i == 0 || j == 0) store[i][j] = 0;
			else if(weights[i-1] <= j) store[i][j] = max(values[i-1] + store[i-1][j-weights[i-1]], store[i-1][j]);
			else store[i][j] = store[i-1][j];
		}
	}
	return store[n][capacity];
}

int debug_dynamic(){
	int values[] = {1, 2, 3, 4, 5};
	int weights[] = {1, 1, 2, 2, 3};
	int capacity = 4;
	int soln = dynamic(values, weights, capacity, 5);
	cout << soln << endl;
	return 0;
}
