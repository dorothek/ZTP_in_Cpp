#include<cstdio>
#include<iostream>
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
	Dane* nast = NULL;
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

template<typename Obj>
class Stos {
public:
	Obj* poczatek = NULL;
	void put(Obj* obiekt) { //poloz na stos
		if (poczatek == NULL) {
			poczatek = obiekt;
		}
		else {
			Obj* zapamietaj_poczatek = poczatek;
			while (poczatek->nast != NULL) {
				poczatek = poczatek->nast;
			}
			poczatek->nast = obiekt;
			poczatek = zapamietaj_poczatek;
		}
	}
	Obj* get() { //zdejmuje ze stosu
		Obj* zwracany = NULL;

		if (poczatek == NULL) { // brak elementów
			zwracany = NULL;
		}
		else if (poczatek->nast == NULL) {// jeden element
			zwracany = poczatek;
			poczatek = NULL;
		}
		else { // co najmniej dwa elementy
			Obj* wrk_poczatek = poczatek;
			while (wrk_poczatek->nast != NULL && wrk_poczatek->nast->nast != NULL) {
				wrk_poczatek = wrk_poczatek->nast;
			}
			zwracany = wrk_poczatek->nast;
			wrk_poczatek->nast = NULL;
		}
		return zwracany;
	}
	Obj* top() {
		Obj* zapamietaj_poczatek = poczatek;
		Obj* zwracany = NULL;

		if (poczatek == NULL) { // brak elementów
			zwracany = NULL;
		}
		else if (poczatek->nast == NULL) {// jeden element
			zwracany = poczatek;
		}
		else { // co najmniej dwa elementy
			while (poczatek->nast != NULL && poczatek->nast->nast != NULL) {
				poczatek = poczatek->nast;
			}
			zwracany = poczatek->nast;
		}
		poczatek = zapamietaj_poczatek;
		return zwracany;
	}
	int size() {
		int ile = 0;
		Obj* zapamietaj_poczatek = poczatek;
		while (poczatek != NULL) {
			poczatek = poczatek->nast;
			ile++;
		}
		poczatek = zapamietaj_poczatek;
		return ile;
	}
	Stos() {
	}
	~Stos() {
		if (poczatek != NULL) {
			while (poczatek->nast != NULL) {
				Obj* tmp_poczatek = poczatek;
				poczatek = poczatek->nast;
				delete tmp_poczatek;
			}
			delete poczatek;
		}
	}
};

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

void generuj_raport(Stos<Dane>stos, string nazwa) {
	Dane tab[3];
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
		Dane suma = { 0,' ',0,0};
		for (int i = 0; i < 4; i++) {
			tab[i] = *stos.get();
			plik << tab[i];
			suma += tab[i];
		}
		plik << "+------+----------+-------+------+" << endl;
		plik << suma;
		plik << "+------+----------+-------+------+" << endl;
		exit(0);
	}
	else {
		cout << "Blad otwarcia pliku";
		exit(1);
	}
	plik.close();
}

int main() {
	Stos<Dane>stos;
	Dane p1 = {1,"Pierwsza",17,0.3};
	Dane p2 = {2,"Druga",17.5,0.3};
	Dane p3 = {3,"Trzecia",18,0.3};
	Dane p4 = {4,"Czwarta",18.5,0.3};
	stos.put(&p1);
	stos.put(&p2);
	stos.put(&p3);
	stos.put(&p4);
	cout << "Podaj nazwe pliku: ";
	string nazwa;
	cin >> nazwa;
	generuj_raport(stos, nazwa);
	return 0;
}