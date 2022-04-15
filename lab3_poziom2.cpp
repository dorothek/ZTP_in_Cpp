#include <iostream>
#include <string>
#include <fstream>

#define NAZWA_PLIKU "tabela.txt"

using namespace std;

class Blad_pliku_HTML {
protected:
	int numer_linii;
public:
	Blad_pliku_HTML(int linia) {
		numer_linii = linia;
	}
	friend ostream& operator << (ostream& stream, Blad_pliku_HTML& blad) {
		return stream << "Blad pliku HTML, linia " << blad.numer_linii << endl;
	}
};

class Brak_znacznika_konczacego : public Blad_pliku_HTML {
	string opis;
public:
	Brak_znacznika_konczacego(int linia, string opis_bledu):Blad_pliku_HTML(linia) {
		opis = opis_bledu;
	}
	friend ostream& operator << (ostream& stream, Brak_znacznika_konczacego& blad) {
		return stream << "Blad pliku HTML, linia " << blad.numer_linii << " brak znacznika konczacego " << blad.opis<< endl;
	}
};

class Bledny_znacznik_konczacy : public Blad_pliku_HTML {
	string opis;
public:
	Bledny_znacznik_konczacy(int linia, string opis_bledu) :Blad_pliku_HTML(linia) {
		opis = opis_bledu;
	}
	friend ostream& operator << (ostream& stream, Bledny_znacznik_konczacy& blad) {
		return stream << "Blad pliku HTML, linia " << blad.numer_linii << " bledny znacznik konczacy " << blad.opis << endl;
	}
};


class Brak_odpowiadajacego_znacznika_konczacego : public Blad_pliku_HTML {
	string opis;
public:
	Brak_odpowiadajacego_znacznika_konczacego(int linia, string opis_bledu) :Blad_pliku_HTML(linia) {
		opis = opis_bledu;
	}
	friend ostream& operator << (ostream& stream, Brak_odpowiadajacego_znacznika_konczacego& blad) {
		return stream << "Blad pliku HTML, linia " << blad.numer_linii << " brak odpowiadajacego znacznika konczacego " << blad.opis << endl;
	}
};

class Wczesny_koniec : public Blad_pliku_HTML {
public:
	Wczesny_koniec(int linia) :Blad_pliku_HTML(linia) {	}
	friend ostream& operator << (ostream& stream, Wczesny_koniec& blad) {
		return stream << "Blad pliku HTML, linia " << blad.numer_linii << " koniec pliku przed odpowiednim znacznikiem zamykajacym " << endl;
	}
};


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

void Stos::dodaj(string znak) {
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
void Stos::zdejmij() {
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
	size_t poczatek = line.find('<');
	size_t koniec = line.find('>');
	if (koniec > poczatek) {
		return line.substr(poczatek + 1, koniec - poczatek - 1);
	}
	else {
		return "";
	}
}

string znajdz_znacznik_konczacy(string line) {
	size_t poczatek = line.find_last_of('<');
	size_t koniec = line.find_last_of('>');
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
				znacznik = znacznik.substr(1, znacznik.length() - 1);
			}
			//cout << "Znaleziony znacznik: " << znacznik << " konczacy "<< konczacy << endl;
			if (stos_znacznikow == NULL) {
				if (znacznik != "TABLE" || konczacy) {
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
						throw Brak_znacznika_konczacego(numer_lini," oczekiwany /" + znacznik + " znaleziony " + znacznik_konczacy);
						//throw "Brak znacznika konczacego";
					}
					if (znacznik_konczacy.substr(1, znacznik_konczacy.length() - 1) != znacznik) {
						throw Bledny_znacznik_konczacy(numer_lini, " oczekiwany /" + znacznik + " znaleziony " + znacznik_konczacy.substr(1, znacznik_konczacy.length() - 1));
						//throw "Bledny znacznik konczacy";
					}
				}
				else {
					if (konczacy) {
						if (stos_znacznikow->podaj_ostatni_znacznik() != znacznik)
						{
							throw Brak_odpowiadajacego_znacznika_konczacego(numer_lini, "szukany " + stos_znacznikow->podaj_ostatni_znacznik()+ " znaleziony " + znacznik);
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
			throw Wczesny_koniec(numer_lini);
			//throw "Koniec pliku przed odpowiednim znacznikiem zamykajacym";
		}
		cout << "Plik poprawny" << endl;
	}
	
	catch (Brak_znacznika_konczacego& blad) {
		cout << blad << endl;
	}
	catch (Bledny_znacznik_konczacy& blad) {
		cout << blad << endl;
	}
	catch (Brak_odpowiadajacego_znacznika_konczacego& blad) {
		cout << blad << endl;
	}
	catch (Wczesny_koniec& blad) {
		cout << blad << endl;
	}
	catch (Blad_pliku_HTML& blad) {
		cout << blad<<endl;
	}
	catch (const char napis[100]) {
		cout << napis << " w lini:" << numer_lini << endl;
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