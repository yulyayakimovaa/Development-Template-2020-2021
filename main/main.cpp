#include <iostream>
#include "Text.h"

using namespace std;

int main()
{

  char* temp = "Qwerty. \nAsd fgh zxc.";
  Text A(temp);
  TextIter B = A.Find("w");

  A.InsertData("New", B);

  cout << endl << A;
  return 0;
}