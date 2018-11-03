#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;
/*
g++ 11_binary_search_in_matrix.cpp -o 11_binary_search_in_matrix.out
*/

class Matrix {
public:
	//setw sets the width parameter of the stream out or in to exactly n.
	void printMatrix(int a[][4]){
		cout << "input: " << endl;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j)
				cout << setw(2) << a[i][j] << " ";
			cout << endl;
		}		
	}

	/*
	 * Does a binary search in a matrix of values
	 * if the number is greater than x : traverse - right to Left, up to down
	 * if the number is smaller than x : traverse - up to donw, right to left
	 * @param a[][4] double array 
	 * @param m horizontle row
	 * @param n vertical column
	 * @param x The number you are searching for
	 * @return returns the random word string
	 */
	bool binary_search_in_matrix(int a[][4], int m, int n, int x) {
		int row = 0, col = n-1;

		while (row < m && col >= 0) {
			printf("(%2d,%2d), val: %2d\n", row, col, a[row][col]);

			if (a[row][col] == x) {
				cout << "find " << x << " at " << row << "," << col << endl;
				return true;
			} else if (a[row][col] > x) {
				if (col > 0) --col;
				else ++row;
			} else { // a[row][col] < x
				if (row < m-1) ++row;
				else --col;
			}
		}
		return false;
	}
};

int main()
{
	Matrix sol;
	int a[4][4] = { {15, 20, 70, 85},
					{20, 35, 80, 96},
					{30, 55, 95, 105},
					{40, 80, 120, 120} };

	sol.printMatrix(a);


	sol.binary_search_in_matrix(a, 4, 4, 40);
	
	return 0;
}
