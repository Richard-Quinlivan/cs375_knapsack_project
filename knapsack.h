#pragma once

//header file for the whole program: has random array utility

#include <iostream>
#include <fstream>
#include <chrono>
#include <stdlib.h>
#include <time.h>

#define SAMPLE_SIZE 100 //anything higher and we get a stack overflow: the algorithms are space-intensive

int* create_random_array(int size, int bound);

int brute_force_rec(int values[], int weights[], int capacity, int index);

int knapsack_rec(int values[], int weights[], int capacity, int index, int **table);

int dynamic(int values[], int weights[], int capacity, int n);
