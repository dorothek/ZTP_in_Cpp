#include<cstdio>
#include <iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>

using namespace std;

struct Dane {
	int id;
	char nazwa[10];
	double temp;
	double pojemn;
	Dane operator+=(Dane& nazwa) {
		temp += nazwa.temp;
		pojemn += nazwa.pojemn;
		return *this;
	}
};

template <typename T, int rozmiar>
class Tablica {
	T A[rozmiar];
public:
	T& operator[](int index);
};

template <typename T, int rozmiar>
T& Tablica<T, rozmiar>::operator[](int index)
{
	if (index >= rozmiar || index < 0)
		return A[0];
	else
		return A[index];
}

fstream& operator<<(fstream& stream, Dane wiersz) {
	//id
	stream << "|";
	stream.width(6);
	stream.fill('0');
	stream << right << wiersz.id << "|";
	//nazwa
	stream.width(10);
	stream.fill(' ');
	stream << left << wiersz.nazwa << "|";
	//temp
	stream.width(7);
	stream.precision(1);
	stream << right << fixed << wiersz.temp << "|";
	stream.width(6);
	stream.precision(0);
	stream << right << wiersz.pojemn << "|" << endl;
	return stream;
}

void generuj_raport(Tablica<Dane,4> tab,string nazwa) {
	fstream plik;
	plik.open(nazwa, ios::out);
	if (plik.is_open()) {
		cout << "Zapis danych do pliku..." << endl;
		time_t czas;
		time(&czas);
		plik.width(34);
		plik << right << asctime(localtime(&czas)) << endl;
		plik << left << getenv("COMPUTERNAME") << endl;
		plik << "+------+----------+-------+------+" << endl;
		plik << "|  ID  |   nazwa  | temp. |pojemn|" << endl;
		plik << "+------+----------+-------+------+" << endl;
		Dane suma = { 0,' ',0,0 };
		for (int i = 0; i < 4; i++) {
			plik << tab[i];
			suma += tab[i];
		}
		plik << "+------+----------+-------+------+" << endl;
		plik << suma;
		plik << "+------+----------+-------+------+" << endl;
	}
	else {
		cout << "Blad otwarcia pliku";
		exit(1);
	}
	plik.close();
}

int main() {
	Tablica<Dane, 4>tab;
	tab[0].id = 1;
	strcpy(tab[0].nazwa, "Pierwsza");
	tab[0].temp = 18.0;
	tab[0].pojemn = 0.3;
	tab[1].id = 2;
	strcpy(tab[1].nazwa, "Druga");
	tab[1].temp = 17.5;
	tab[1].pojemn = 0.3;
	tab[2].id = 3;
	strcpy(tab[2].nazwa, "Trzecia");
	tab[2].temp = 19.0;
	tab[2].pojemn = 0.3;
	tab[3].id = 4;
	strcpy(tab[3].nazwa, "Czwarta");
	tab[3].temp = 18.5;
	tab[3].pojemn = 0.3;
	cout << "Podaj nazwe pliku: ";
	string nazwa;
	cin >> nazwa;
	generuj_raport(tab,nazwa);
	cout << "Koniec programu";
	return 0;
}