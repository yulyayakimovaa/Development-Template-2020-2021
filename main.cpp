#include <iostream>
#include <string>
#include <D:\язык си программы\treeeee\treeeee\tree.h>


int main()
{
	setlocale(LC_ALL, "Russian");

	string str = "ехал по дороге по полю";

	Tree tr(str);
	cout << tr.getCount("по") << endl;

	return 0;
}