#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <set>
#include <numeric>
#include <math.h>

using namespace std;

double chi(double R, double S)
{
	if (R+S == 0){
		return 0;
	}
	return (pow((R - S), 2.0) / (R + S));
}

int main() {
	srand(time(NULL));
	multiset<int> r, s; // bufor do zapisywania obserwacji
	for (int i = 0;i < 1000; i++){
		r.insert(rand() % 10); // dodaj wynik nowej obserwacji
		s.insert(rand() % 10); // dodaj wynik nowej obserwacji
	}
	vector<int>R(10), S(10);
	cout << "Zbior R: ";
	int gatunek = 0;
	for_each(R.begin(), R.end(), [&gatunek, &r](int& ptak) {ptak = r.count(gatunek++); cout << ptak << " ";});
	
	cout << endl<< "Zbior S: ";
	gatunek = 0;
	for_each(S.begin(), S.end(), [&gatunek, &s](int& ptak) {ptak = s.count(gatunek++); cout << ptak << " ";});

	double wynik = 0;
	wynik = inner_product(R.begin(), R.end(), S.begin(), (double)0, plus<double>(), chi);
	cout << endl<< "Suma chi kwadrat: " << wynik;
}