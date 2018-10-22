#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/*
g++ binarySearch.cpp -o binarySearch.out
./binarySearch.out 20 y
*/

// This allows me to sort using the qsort() function in C. It returns a
// positive integer if (*a > *b), a negative integer if (*b < *a), and zero if
// (*a == *b).
int mycmp(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

class BinSearch {
public:

	BinSearch(int len):m_Length(len){}

	~BinSearch(){}

	void populateArray(int array[]){	
		
		srand(time(NULL));
		
		// Populate with random integers ranging from 0 to 20
		for (int i = 0; i < m_Length; i++)
			array[i] = rand() % 20 + 1;
	}

	void printArray(int array[]){
		for(int i = 0; i < m_Length; i++){
			string printString = (i == m_Length -1) ? "\n" : " ";
			cout << array[i] << printString;
		}
	}

	int getRandomNumber(int range){
		srand(time(NULL));
		return rand() % range + 1;
	}

	void performBinarySearch(char *argv[], BinSearch& bSearch, int array[], int randNumber){
		// perform either the debug bSearch or regular depending on cmd line args
		if( argv[2] && (argv[2] == string("y")) ){
			// perform the binary search
			if(bSearch.debug_binarySearch(array, bSearch.m_Length, randNumber)){
				cout << "bSearch found the item:" << randNumber << endl;
			} else {
				cout << "bSearch could not find the item:" << randNumber << endl;
			}		
		} else {
			//perform the binary search
			if(bSearch.binarySearch(array, bSearch.m_Length, randNumber)){
				cout << "bSearch found the item:" << randNumber << endl;
			} else {
				cout << "bSearch could not find the item:" << randNumber << endl;
			}
		}
	}

	/* this does a binary search with debug statments on
	 * @param array array that will be searched
	 * n lenght of array that will be sorted
	 * key the element that you are searching for
	 */
	int debug_binarySearch(int array[], int n, int key)
	{
		int lo = 0, hi = n - 1, mid;
		
		while (hi >= lo)
		{
			mid = lo + (hi  - lo) / 2;
			printf("mid:%d = lo:%d + (hi:%d  - lo:%d) / 2 \n", mid, lo, hi, lo);

			if (key < array[mid]){
				hi = mid - 1;
				printf("key:%d < array[mid:%d] hence ->", key, mid);
				printf("hi:%d = mid%d - 1", hi, mid);
			}
			
			// if the key is greater than the value at mid, consider only the right
			// half of the array
			else if (key > array[mid]){
				lo = mid + 1;
				printf("key:%d > array[mid:%d] hence ->", key, mid);
				printf("lo:%d = mid:%d + 1", lo, mid);
			}
			
			// otherwise, we found the key!
			else{
				cout << "we found the key !" << endl;
				return 1;
			}
			cout << ":endWhile" << endl;
		}
		
		return 0;
	}

	/* this does a binary search
	 * @param array array that will be searched
	 * n lenght of array that will be sorted
	 * key the element that you are searching for
	 */
	int binarySearch(int array[], int n, int key)
	{
		int lo = 0, hi = n - 1, mid;
		
		while (hi >= lo)
		{
			// Why use this instead of mid = (hi + lo) / 2, even though they're
			// algebraically equivalent?
			mid = lo + (hi  - lo) / 2;
			
			// if the key is less than the value at mid, consider only the left half
			// of the array
			if (key < array[mid])
				hi = mid - 1;
			
			// if the key is greater than the value at mid, consider only the right
			// half of the array
			else if (key > array[mid])
				lo = mid + 1;
			
			// otherwise, we found the key!
			else
				return 1;
		}
		
		return 0;
	}

	int m_Length;

};

/*
 * @param argv is array of character pointers listing all the arguments.
 * @param is int and stores number of command-line arguments passed by 
 * the user including the name of the program. So if we pass a value to a 
 * program, value of argc would be 2
 */
int main(int argc, char** argv)
{
	cout << "Param1 range of array to sort" << endl;
	cout << "Param2 use debug BinarySearch y= yes, n = No, null will default to NO" << endl;
	int arrayLen = atoi(argv[1]);
	BinSearch bSearch(arrayLen);

	int array[arrayLen];

	bSearch.populateArray(array);

	bSearch.printArray(array);

	// Sort the array using C's built-in QuickSort function. This is using a
	// function pointer. It's amazing. You should google "c qsort" and read
	// about how it works.
	qsort(array, bSearch.m_Length, sizeof(int), mycmp);

	cout << "Sorted Array" << endl;

	bSearch.printArray(array);

	// random number we will search for in the binary search
	int randNumber = bSearch.getRandomNumber(arrayLen);

	// perform either the debug bSearch or regular depending on cmd line args
    bSearch.performBinarySearch(argv, bSearch, array, randNumber);

	return 0;
}