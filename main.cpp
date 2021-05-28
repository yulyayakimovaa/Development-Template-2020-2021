#include <iostream>

using namespace std;

void fillDepth(int par[], int i, int depth[])
{
	if (depth[i])
		return;
	if (par[i] == -1)
	{
		depth[i] = 1;
		return;
	}
	if (depth[par[i]] == 0)
		fillDepth(par, par[i], depth);
	depth[i] = depth[par[i]] + 1;
}

int findHeight(int par[], int n)
{
	int *depth= new int[n];
	for (int i = 0; i < n; i++)
		depth[i] = 0;
	for (int i = 0; i < n; i++)
		fillDepth(par, i, depth);
	int ht = depth[0];
	for (int i = 1; i < n; i++)
		if (ht < depth[i])
			ht = depth[i];
	return ht;
}

int main()
{
	int par[] = { 3,4,3,-1,3,7,1,3,1,4 };
	int n = sizeof(par) / sizeof(par[0]);
	cout << "Height is " << findHeight(par, n) << endl;
	return 0;
}