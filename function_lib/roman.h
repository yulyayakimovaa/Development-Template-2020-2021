#pragma once 

#include <iostream>
using namespace std;

class roman {

public:
	string value;
	roman(string _value = "") { value = _value; }
	friend bool operator == (const roman& _r1, const roman& _r2);
	void add(string _r) {
		value += _r;
	}
	char GetRom(int i) { return value[i]; }
	int GetLenRom() { return value.length(); }
	friend istream& operator >>(istream& in, roman& r)
	{
		in >> r.value;
		return in;
	}
	friend ostream& operator <<(ostream& out, const roman& r)
	{
		out << r.value;
		return out;
	}
};

struct arabic {

public:
	int value;
	arabic(int _value = 0) { value = _value; }
	friend bool operator == (const arabic& _a1, const arabic& _a2);
	void add(int _a) {
		value += _a;
	}
	int GetAr() { return value; }
	friend istream& operator >>(istream& in, arabic& a)
	{
		in >> a.value;
		return in;
	}
	friend ostream& operator <<(ostream& out, const arabic& a)
	{
		out << a.value;
		return out;
	}
};


class Convertor {
	roman rm;
	arabic ar;

public:
	Convertor(roman _rm, arabic _ar) { rm = _rm; ar = _ar; }

	friend arabic toArabic(roman t);
	friend roman toRoman(arabic t);

	void printRm();
	void printAr();

	bool checkRoman(roman& t);
	bool checkArabic(arabic& t);
};
