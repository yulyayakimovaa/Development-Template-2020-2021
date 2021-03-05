#include "roman.h"
using namespace std;


bool Convertor::checkRoman(roman& t) {
	for (int i = 0; i < t.GetLenRom(); i++)
	{
		if ((t.GetRom(i) != 'M') && (t.GetRom(i) != 'D') && (t.GetRom(i) != 'C') && (t.GetRom(i) != 'L') && (t.GetRom(i) != 'X') && (t.GetRom(i) != 'V') && (t.GetRom(i) != 'I'))
			return false;
	}
	for (int i = 0; i < t.GetLenRom(); i++) {
		int j = i;
		while (t.GetRom(i) == 'I') {
			j++;
		}
		if (j - i > 3) return false;
		while (t.GetRom(i) == 'X') {
			j++;
		}
		if (j - i > 3) return false;
		while (t.GetRom(i) == 'C') {
			j++;
		}
		if (j - i > 3) return false;
		while (t.GetRom(i) == 'M') {
			j++;
		}
		if (j - i > 3) return false;
		i = j;
	}

	return true;
}

bool Convertor::checkArabic(arabic& t)
{
	if ((t.value >= 4000) || (t.value < 0))
		return false;
	else
		return true;
}

arabic toArabic(roman t) {
	arabic res;
	res.value = 0;
	int i = 0;

	while (t.GetRom(i) == 'M') {
		res.value += 1000;
		i++;
	}

	if (t.GetRom(i) == 'C') {
		if (t.GetRom(i + 1) == 'M') {
			res.value += 900;
			i += 2;
		}
		else
			if (t.GetRom(i + 1) == 'D') {
				res.value += 400;
				i += 2;
			}
			else {
				res.value += 100;
				i++;
			}
	}
	if (t.GetRom(i) == 'D') {
		res.value += 500;
		i++;
	}
	while (t.GetRom(i) == 'C') {
		res.value += 100;
		i++;
	}
	if (t.GetRom(i) == 'X') {
		if (t.GetRom(i + 1) == 'C') {
			res.value += 90;
			i += 2;
		}
		else
			if (t.GetRom(i + 1) == 'L') {
				res.value += 40;
				i += 2;
			}
			else {
				res.value += 10;
				i++;
			}
	}
	if (t.GetRom(i) == 'L') {
		res.value += 50;
		i++;
	}
	while (t.GetRom(i) == 'X') {
		res.value += 10;
		i++;
	}
	if (t.GetRom(i) == 'I') {
		if (t.GetRom(i + 1) == 'X') {
			res.value += 9;
			i += 2;
		}
		else
			if (t.GetRom(i + 1) == 'V') {
				res.value += 4;
				i += 2;
			}
			else {
				res.value += 1;
				i++;
			}
	}
	if (t.GetRom(i) == 'V') {
		res.value += 5;
		i += 1;
	}
	while (t.GetRom(i) == 'I') {
		res.value += 1;
		i++;
	}
	return res;
}


roman toRoman(arabic t) {
	roman res;
	int val = t.value;
	while (val > 1000) {
		res.add("M");
		val -= 1000;
	}
	if (val / 900 > 0) {
		res.add("CM");
		val -= 900;
	}
	if (val / 500 > 0) {
		res.add("D");
		val -= 500;
	}
	if (val / 400 > 0) {
		res.add("CD");
		val -= 400;
	}

	while (val > 100) {
		res.add("C");
		val -= 100;
	}

	if (val / 90 > 0) {
		res.add("XC");
		val -= 90;
	}
	if (val / 50 > 0) {
		res.add("L");
		val -= 50;
	}
	if (val / 40 > 0) {
		res.add("XL");
		val -= 40;
	}

	while (val > 10) {
		res.add("X");
		val -= 10;
	}

	if (val / 9 > 0) {
		res.add("IX");
		val -= 9;
	}
	if (val / 5 > 0) {
		res.add("V");
		val -= 5;
	}
	if (val / 4 > 0) {
		res.add("IV");
		val -= 4;
	}

	while (val > 0) {
		res.add("I");
		val -= 1;
	}

	return res;
}

void Convertor::printAr() {
	cout << ar.value << endl;
}
void Convertor::printRm() {
	cout << rm.value << endl;
}

bool operator == (const roman& _r1, const roman& _r2) {
	if (_r1.value != _r2.value) return false;
	else return true;
}

bool operator == (const arabic& _a1, const arabic& _a2) {
	if (_a1.value != _a2.value) return false;
	else return true;
}