#include <iostream>
#include <string>
#include <fstream>

#define NAZWA_PLIKU "tabela.txt"

using namespace std;

class Stos {
public:
	Stos* nast;
	Stos* poprz;
	string znacznik = "";
	Stos(string znak)
	{
		nast = NULL;
		poprz = NULL;
		znacznik = znak;
	}
	void dodaj(string znak);
	void zdejmij();
	string podaj_ostatni_znacznik();
};

void Stos::	dodaj(string znak) {
	{
		Stos* wsk = NULL;
		wsk = this;
		while (wsk->nast != NULL)
		{
			wsk = wsk->nast;
		}
		wsk->nast = new Stos(znak);
		wsk->nast->poprz = wsk;
		wsk->nast->znacznik = znak;
		//cout << "Dodaje" << wsk->nast->znacznik<< endl;
	}
}
void Stos::zdejmij(){
		Stos* wsk = NULL;
		wsk = this;
		while (wsk->nast != NULL)
		{
			wsk = wsk->nast;
		}
		if (wsk->poprz != NULL)
		{
			wsk->poprz->nast = NULL;
		}
		if (wsk->poprz == NULL)
		{
			wsk->nast = NULL;
		}
		//cout << "Zdejmuje" << wsk->znacznik << endl;
		delete wsk;
}

string Stos::podaj_ostatni_znacznik() {
	Stos* wsk = NULL;
	wsk = this;
	while (wsk->nast != NULL)
	{
		wsk = wsk->nast;
	}

	return wsk->znacznik;
}

Stos* stos_znacznikow = NULL;


bool czy_konczacy(string znacznik) {
	if (znacznik[0] == '/') {
		return true;
	}
	else {
		return false;
	}
}

string znajdz_pierwszy_znacznik(string line) {
	size_t poczatek=line.find('<');
	size_t koniec=line.find('>');
	if (koniec > poczatek) {
		return line.substr(poczatek+1,koniec-poczatek-1);
	}
	else {
		return "";
	}
}

string znajdz_znacznik_konczacy(string line) {
	size_t poczatek=line.find_last_of('<');
	size_t koniec=line.find_last_of('>');
	if (koniec > poczatek) {
		return line.substr(poczatek + 1, koniec - poczatek - 1);
	}
	return "";
}

void funkcja_sprawdzajaca_html(fstream& plik) {
	string line = "";
	int numer_lini = 0;
	int dlugosc = 0;
	string pomocniczy = "";
	try {
		while (!plik.eof()) {
			getline(plik, line);
			dlugosc = line.length();
			numer_lini++;
			string znacznik = znajdz_pierwszy_znacznik(line);
			bool konczacy = czy_konczacy(znacznik);
			if (konczacy) {
				znacznik=znacznik.substr(1,znacznik.length()-1);
			}
			//cout << "Znaleziony znacznik: " << znacznik << " konczacy "<< konczacy << endl;
			if (stos_znacznikow == NULL ) {
				if (znacznik != "TABLE"||konczacy) {
					cout << "To nie jest tabela w HTML" << endl;
					exit(0);
				}
				else {
					stos_znacznikow = new Stos("");
					stos_znacznikow->dodaj(znacznik);
				}
			}
			else {
				if ((znacznik == "CAPTION" || znacznik == "TH" || znacznik == "TD") && !konczacy) {
					string znacznik_konczacy = znajdz_znacznik_konczacy(line);
					//cout << znacznik_konczacy << endl;
					if (!czy_konczacy(znacznik_konczacy)) {
						throw "Brak znacznika konczacego";
					}
					if (znacznik_konczacy.substr(1, znacznik_konczacy.length() - 1) != znacznik) {
						throw "Bledny znacznik konczacy";
					}
				}
				else {
					if (konczacy) {
						if (stos_znacznikow->podaj_ostatni_znacznik() != znacznik)
						{
							//cout << "Szukany " << znacznik << " znaleziony " << stos_znacznikow->podaj_ostatni_znacznik() << endl;

							throw "Brak odpowiadajacego znacznika konczacego";
						}
						stos_znacznikow->zdejmij();
					}
					else {
						stos_znacznikow->dodaj(znacznik);
					}
				}
			}
		}
		if (stos_znacznikow->podaj_ostatni_znacznik() != "") {
			throw "Koniec pliku przed odpowiednim znacznikiem zamykajacym";
		}
		cout << "Plik poprawny" << endl;
	}
	catch(const char napis[100]) {
		cout << napis <<" w lini:"<<numer_lini << endl;
	}
}

int main() {
	fstream plik;
	plik.open(NAZWA_PLIKU, ios::in);
	if (plik.good()) {
		funkcja_sprawdzajaca_html(plik);
	}
	else {
		cout << "Operacja otwierania pliku nie powiodla sie" << endl;
	}
	plik.close();
	cout << "Koniec programu";
	return 0;
}