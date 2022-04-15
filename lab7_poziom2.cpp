#include<iostream>
#include<vector>
#include<ctime>
#include <algorithm>
#include<set>
#include<numeric>
#include<math.h>

using namespace std;

int falszywa_kostka() {
	int wynik= rand() % 10;
	int tab[10] = {1,2,6,3,3,4,4,5,5,5}; //liczby w tabelce s¹ rozmieszczone wg prawdopodobienstwa podanego w zadaniu
	return tab[wynik];
}

void podziel(double& pozycja) {
	pozycja=pozycja/100;
}

int main() {
	srand((unsigned)time(NULL));
	multiset<int> rzuty;
	for (int i = 0; i < 100; i++)
	{
		rzuty.insert(falszywa_kostka());
	}
	//liczebnoœæ wyst¹pieñ poszczególnych wartoœci kostki
	vector<int>rozklad(6);
	cout << "Rozklad prawdopodobienstwa: ";
	int ilosc = 1;
	for_each(rozklad.begin(), rozklad.end(), [&ilosc, &rzuty](int& licz) {licz = rzuty.count(ilosc++); cout << licz << " ";});
	
	//dystrybuanta partial_sum
	vector<double>dystrybuanta(6);

	partial_sum(rozklad.begin(), rozklad.end(), dystrybuanta.begin());
	for_each(dystrybuanta.begin(), dystrybuanta.end(), podziel);

	cout <<endl<< "Dystrybuanta: ";
	for (int i = 0; i < 6; i++) {
		cout << dystrybuanta[i] << " ";
	}
	cout<<endl;
}