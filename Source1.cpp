#include <iostream>
#include <ctime>
#include <cstdio>
#include "Source1.h"
using namespace std;
void insertion_sort(int v[], int n) {
	int value;
	int i, j;
	for (i = 1; i < n; i++) {
		value = v[i];
		j = i - 1;
		while (j >= 0 && v[j] > value) {
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = value;
	}
}

// Function to join left and right subarray
int join(int arr[], int left[], int right[],
	int l, int m, int r)
{
	int i;
	for (i = 0; i <= m - l; i++)
		arr[i] = left[i];

	for (int j = 0; j < r - m; j++)
	{
		arr[i + j] = right[j];
	}
}

// Function to store alternate elements in
// left and right subarray
int split(int arr[], int left[], int right[],
	int l, int m, int r)
{
	for (int i = 0; i <= m - l; i++)
		left[i] = arr[i * 2];

	for (int i = 0; i < r - m; i++)
		right[i] = arr[i * 2 + 1];
}

// Function to generate Worst Case
// of Merge Sort
int generateWorstCase(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;

		// Create two auxiliary arrays
		int left[m - l +1];
		int right[r - m];

		// Store alternate array elements
		// in left and right subarray
		split(arr, left, right, l, m, r);

		// Recurse first and second halves
		generateWorstCase(left, l, m);
		generateWorstCase(right, m + 1, r);

		// Join left and right subarray
		join(arr, left, right, l, m, r);
	}
}

void merge(int array[], int const left, int const mid,
	int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne
		= 0, 
		indexOfSubArrayTwo
		= 0;
	int indexOfMergedArray
		= left;

	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne]
			<= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray]
				= leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end){
	if (begin >= end)
		return;

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}


void print_vector(int v[], int n) {
	int i;
	std::cout << "Sorted Array"<<std::endl;
	for (i = 0; i < n; i++) {
		std::cout << v[i] << " ";
		std::cout << std::endl;
	}
}

int main() {

	std::clock_t insertion_time,merge_time;
	double insertion_duration,merge_duration;
	int tmp = 10000;
	int a[10000];
	
	for (int i = 0; i < 10000; i++){
		a[i] = tmp;
		tmp--;
	}
	auto arr_size = sizeof(a) / sizeof(a[0]);

	insertion_time = std::clock();
	insertion_sort(a, arr_size);
    print_vector(a, arr_size);
	insertion_duration = (std::clock() - insertion_time) / (double)CLOCKS_PER_SEC;
	//std::cout << "Insertion-sort processing time: " << insertion_duration << '\n';

	tmp = 10000;
	for (int i = 0; i < 10000; i++) {
		a[i] = tmp;
		tmp--;
	}
	
	generateWorstCase(a, 0, arr_size - 1);
	print_vector(a, arr_size);
	merge_time = std::clock();
	mergeSort(a, 0, arr_size - 1);
	print_vector(a, arr_size);
	merge_duration = (std::clock() - merge_time)/(double)CLOCKS_PER_SEC;
	std::cout << "Insertion-sort processing time: " << insertion_duration << '\n';
	std::cout << "Merge-sort processiong time : " << merge_duration<< std::endl;
}