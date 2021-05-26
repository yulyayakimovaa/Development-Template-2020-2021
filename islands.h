#include <iostream>

using namespace std;

int found_islands(int** arr, int m, int n) 
{
	int Count = 0; int Num = 2;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) 
		{
			if (arr[i][j] == 0) 
			{
				Count++;
				walk(arr, m, n, i, j, Num);
				Num += 2;
			}
		}
	}
	return Count;
}


void walk(int** arr, int m, int n, int i, int j, int N) 
{
	arr[i][j] = N;
	
	if (i + 1 < m) 
	{
		if (arr[i + 1][j] == 0) 
		{
			walk(arr, m, n, i + 1, j, N);
		}
		if(j + 1 < n)
			if (arr[i + 1][j + 1] == 0) 
			{
				walk(arr, m, n, i + 1, j + 1, N);
			}
	}

	if (j + 1 < n) 
	{
		if (arr[i][j + 1] == 0) 
		{
			walk(arr, m, n, i, j + 1, N);
		}
		if(i > 0)
			if (arr[i - 1][j + 1] == 0) 
			{
				walk(arr, m, n, i - 1, j + 1, N);
			}
	}
	
	if (j > 0) 
	{
		if (arr[i][j - 1] == 0)
			walk(arr, m, n, i, j - 1, N);
		if (i > 0)
			if (arr[i - 1][j - 1] == 0)
				walk(arr, m, n, i - 1, j - 1, N);
	}

}


void output(int** arr, int m, int n) 
{
	for (int i = 0; i < m; i++) 
	
	{
		cout << '\n' << "     ";
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << ' ';
		}
	}
}