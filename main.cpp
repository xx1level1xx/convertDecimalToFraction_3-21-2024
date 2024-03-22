#include<iostream>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<vector>
using namespace std;
int primes[1000];
struct fract {
	fract();
	fract(int, int);
	int numerator;
	int denominator;
	void simplify();
	fract add(fract, fract);
	fract add(fract, fract, fract);
	fract operator*(fract);//how comes I don't remember
	void print();
};
int common(int, int, int);
int common(int, int, int, int);
fract deciToFract(double);
double tenthFract(int);
void initialize();
int main() {
	initialize();

	//common(2, 4, 1229);

	double d = 0.99;
	fract converted;
	converted = deciToFract(d);
	converted.print();

	system("pause");
	return 0;
}
void initialize() {
	ofstream fout;
	fout.open("primes.txt");
	int primes[2000];
	primes[0] = 2;
	primes[1] = 3;
	primes[2] = 5;
	int count = 3;
	if (fout.is_open()) {
		for (int i = 2; i < 10000; i++) {
			for (int j = 2; j < i / 2; j++) {
				if (i % j == 0) {
					break;
				}
				if (j + 1 == i / 2) {
					primes[count] = i;
					count++;
				}
			}
		}
		cout << "count " << count << endl;
		for (int i = 0; i < count; i++) {
			cout << primes[i] << " ";
			fout << primes[i] << endl;
		}
		fout.close();
	}
	ifstream fin;
	fin.open("primes.txt");
	string temp = "";
	while (!fin.eof()) {
		fin >> temp;
		cout << temp << endl;
	}
	fin.close();
}
fract deciToFract(double d) {
	int pos= 1;
	double reminder = d - floor(d);
	double eps = 0.00001;
	vector<int> fractNumArr;
	while (abs(reminder) > eps) {
		fractNumArr.push_back((int)(reminder / tenthFract(pos)));
		cout << (int)(reminder / tenthFract(pos)) << endl;
		cout << (int)(reminder / tenthFract(pos)) * tenthFract(pos) << endl;
		reminder -= (int)(reminder / tenthFract(pos)) * tenthFract(pos);
		//reminder = round(reminder);
		cout << reminder << endl;
		//system("pause");
		pos++;
		cout << "test10" << endl;
	}
	fract sum(0,1);
	for (int i=1; i < pos; i++) {
		sum = sum.add(sum,fract(fractNumArr[i], pow(10, i)));
	}
	return sum;
}
int common(int a, int b, int count) {
	//int count = sizeof(primes) / sizeof(int);
	//cout << "count " << count << endl;
	int twos = 0;
	bool oddA = a % 2 ? false : true;
	bool oddB = b % 2 ? false : true;
	while (!(oddA == true && oddB == true)) {
		if (oddA == false && oddB == false) {
			a /= 2;
			b /= 2;
			twos++;
		}
		oddA = a % 2 ? false : true;
		oddB = b % 2 ? false : true;
	}
	int productPrimes = 1;
	for (int i = 0; i < count; i++) {
		if (a % primes[i] == 0 && b % primes[i] == 0) { //0?
			productPrimes *= primes[i];
			a /= primes[i];
			b /= primes[i];
			break;
		}
	}
	return pow(2, twos) * productPrimes;
}
int common(int a, int b, int c, int count) {
	int numPrimes = sizeof(primes) / sizeof(int);
	int productPrimes = 1;
	//int count = 0;
	count = 0;
	int doneFOur = 0;
	for (int i = 0; i < 4; i++) {
		while (count != numPrimes) {
			if (i == 0) {
				if (a % primes[count] == 0 && b % primes[count] == 0 && c % primes[count] == 0) {
					productPrimes *= primes[count];
					a /= primes[count];
					b /= primes[count];
					c /= primes[count];
				}

			}
			else if (i == 1) {
				if (a % primes[count] == 0 && b % primes[count] == 0) {
					productPrimes *= primes[count];
					a /= primes[count];
					b /= primes[count];
				}
			}
			else if (i == 2) {
				if (a % primes[count] == 0 && c % primes[count] == 0) {
					productPrimes *= primes[count];
					//////
					//////
				}
			}
			else if (i == 3) {
				if (b % primes[count] == 0 && c % primes[count] == 0) {
					productPrimes *= primes[count];
					//////
				}
			}
			count++;
		}
	}
	return productPrimes;
}
fract::fract() {
	numerator = 0;
	denominator = 1;
}
fract::fract(int n, int d) {
	numerator = n;
	denominator = d;
}
void fract::simplify() {
	int c = common(numerator, denominator, 1229);
	numerator /= c;
	denominator /= c;
}
fract fract::add(fract a, fract b) {
	a.simplify();
	b.simplify();
	fract temp;
	temp.denominator = common(a.denominator, b.denominator, 1229) * (a.denominator / common(a.denominator, b.denominator, 1229)) * (b.denominator / common(a.denominator, b.denominator, 1229));
	temp.numerator = (a.numerator * common(a.denominator, b.denominator, 1229)) + (b.numerator * common(a.denominator, b.denominator, 1229));
	return temp;
}
fract fract::add(fract a, fract b, fract c) {
	a.simplify();
	b.simplify();
	c.simplify();
	fract temp;
	temp.denominator = common(a.denominator, b.denominator, c.denominator) * (a.denominator / common(a.denominator, b.denominator, c.denominator)) * (b.denominator / common(a.denominator, b.denominator, c.denominator)) * (c.denominator / common(a.denominator, b.denominator, c.denominator));
	temp.numerator = (a.numerator * common(a.denominator, b.denominator, c.denominator)) + (b.numerator * common(a.denominator, b.denominator, c.denominator)) + (c.numerator * common(a.denominator, b.denominator, c.denominator));
	return temp;
}
void fract::print() {
	cout << numerator << "/" << denominator << endl;
}
double tenthFract(int num) {
	double factor = 0.1;
	double result = 1;
	if (num == 0)
	{
		return 1;
	}
	for (int i = 0; i < num; i++)
	{
		result *= factor;
	}
	return result;
}