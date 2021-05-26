#include "islands.h"
#include <conio.h>

using namespace std;

int main() {
	int m, n;
	cin >> m >> n;
	int** arr = new int* [m];
	for (int i = 0; i < m; i++) {
		arr[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j]; // 0 and 1
		}
		cout << endl;
	}

	output(arr, m, n);
	cout << endl << found_islands(arr, m, n) << endl;
	output(arr, m, n);
	_getch();

	return 0;
}