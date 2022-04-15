#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>

using namespace std;

template<typename Obj>
class Stos {
public:
	Obj * poczatek = NULL;
	void put(Obj&obiekt) { //poloz na stos
		if (poczatek == NULL) {
			poczatek = &obiekt;
		}
		else {
			Obj*zapamietaj_poczatek = poczatek;
			while (poczatek!=NULL) {
				poczatek = obiekt.nast;
			}
			poczatek = &obiekt;
			poczatek = zapamietaj_poczatek;
		}
	}
	void get(Obj&obiekt) { //zdejmuje ze stosu
		Obj*zapamietaj_poczatek = poczatek;
		while (poczatek->nast != NULL) {
			poczatek = obiekt->nast;
		}
		delete poczatek;
		poczatek = zapamietaj_poczatek;
	}
	Obj&top() {
		if (poczatek!= NULL) {
			Obj*zapamietaj_poczatek = poczatek;
			while (poczatek->nast != NULL) {
				poczatek = obiekt->nast;
			}
			Obj*zwrot = poczatek;
			poczatek = zapamietaj_poczatek;
			return zwrot;
		}
		else {
			cout << "Stos jest pusty" << endl;
		}
	}
	int size() {
		int ile = 0;
		while (poczatek != NULL) {
			poczatek = poczatek->nast;
			ile++;
		}
		return ile;
	}
	void wypisz() {
	}

	Stos(){
	}
};

class Element{
public:
	int a;
	int b;
	Element*nast;
	Element(int value, int dvalue) {
		a = value;
		b = dvalue;
	}
};

int main() {
	Element*nowy = new Element(3,5);
	Element*nowy1 = new Element(7,1);
	Element*nowy2= new Element(4,4);
	Stos<Element>kolejka;
	kolejka.put(*nowy);
	kolejka.put(*nowy1);
	kolejka.put(*nowy2);
	int rozmiar=kolejka.size();
	cout << rozmiar << endl;
	kolejka.wypisz();
}

//program z PO z lab 14
//
//class Samochod {
//public:
//	string nazwa;
//	double cena;
//	string rodzaj_silnika;
//
//	//getery
//	string get_nazwa()
//	{
//		return nazwa;
//	};
//	double get_cena()
//	{
//		return cena;
//	};
//	string get_rodzaj_silnika()
//	{
//		return rodzaj_silnika;
//	};
//	//setery
//	void set_nazwa(string value)
//	{
//		nazwa = value;
//	}
//	void set_cena(double value)
//	{
//		cena = value;
//	}
//	void set_rodzaj_silnika(string value)
//	{
//		rodzaj_silnika = value;
//	}
//
//	virtual void wypisz()
//	{
//		cout << nazwa << "\t" << cena << "\t" << rodzaj_silnika << "\t";
//	}
//	void wypiszF(FILE* outFile)
//	{
//		fprintf(outFile, "%s %lf %s ", nazwa, cena, rodzaj_silnika);
//	}
//
//	//konstruktor domyslny
//	Samochod()
//	{
//		nazwa = "xxx";
//		cena = 0;
//		rodzaj_silnika = "B";
//	}
//	//konstruktor kopiujacy
//	Samochod(Samochod* stary_samochod)
//	{
//		nazwa = stary_samochod->nazwa;
//		cena = stary_samochod->cena;
//		rodzaj_silnika = stary_samochod->rodzaj_silnika;
//	}
//
//	//konstruktor z argumentami
//	Samochod(string name, double price, string engine)
//	{
//		nazwa = name;
//		cena = price;
//		rodzaj_silnika = engine;
//	}
//
//public:
//	Samochod* nast = NULL;
//};
//
//class Samochod_Ciezarowy;
//
//class Samochod_Osobowy : public Samochod {
//public:
//	double pojemnosc_bagaznika;
//	char typ_sylwetki;
//	//H - hatchback, S – sedan, K – kombi, V - van
//
//	//konstruktor domyslny
//	Samochod_Osobowy();
//	//konstruktor kopiujacy
//	Samochod_Osobowy(Samochod_Osobowy* stary_samochod_osobowy);
//	//konstruktor z argumentami
//	Samochod_Osobowy(double pojemnosc, char sylwetka, string name, double price, string engine);
//	Samochod_Osobowy(string name);
//
//	void wypiszF(FILE* outFile);
//	//getery
//	double get_pojemnosc_bagaznika();
//	char get_typ_sylwetki();
//	//setery
//	void set_pojemnosc_bagaznika(double value);
//	void set_pojemnosc_bagaznika(char value);
//	void wypisz();
//	Samochod_Osobowy& operator=(const Samochod_Osobowy& obj);
//	Samochod_Osobowy& operator+(const Samochod_Osobowy& obj);
//	Samochod_Osobowy& operator=(const Samochod_Ciezarowy& obj);
//	Samochod_Osobowy& operator+(const Samochod_Ciezarowy& obj);
//};
//
//
//class Samochod_Ciezarowy : public Samochod {
//public:
//	double ladownosc;
//	int liczba_kol;
//
//	void wypiszF(FILE* outFile);
//	//getery
//	double get_ladownosc();
//	int get_liczba_kol();
//	//setery
//	void set_ladownosc(double value);
//	void set_liczba_kol(int value);
//	void wypisz();
//	Samochod_Ciezarowy& operator=(const Samochod_Ciezarowy& obj);
//	Samochod_Ciezarowy& operator+(const Samochod_Ciezarowy& obj);
//	Samochod_Ciezarowy& operator=(const Samochod_Osobowy& obj);
//	Samochod_Ciezarowy& operator+(const Samochod_Osobowy& obj);
//
//	//konstruktor domyslny
//	Samochod_Ciezarowy();
//	//konstruktor kopiujacy
//	Samochod_Ciezarowy(Samochod_Ciezarowy* stary_samochod_ciezarowy);
//	//konstruktor z argumentami
//	Samochod_Ciezarowy(double ladownosc_s, int kola, string name, double price, string engine);
//	Samochod_Ciezarowy(string name);
//};
//
//void Samochod_Osobowy::wypiszF(FILE* outFile)
//{
//	Samochod::wypiszF(outFile);
//	fprintf(outFile, "%lf %c\n", pojemnosc_bagaznika, typ_sylwetki);
//}
////getery
//double Samochod_Osobowy::get_pojemnosc_bagaznika()
//{
//	return pojemnosc_bagaznika;
//}
//char Samochod_Osobowy::get_typ_sylwetki()
//{
//	return typ_sylwetki;
//}
////setery
//void Samochod_Osobowy::set_pojemnosc_bagaznika(double value)
//{
//	pojemnosc_bagaznika = value;
//}
//void Samochod_Osobowy::set_pojemnosc_bagaznika(char value)
//{
//	typ_sylwetki = value;
//}
//void Samochod_Osobowy::wypisz()
//{
//	Samochod::wypisz();
//	cout << pojemnosc_bagaznika << "\t" << typ_sylwetki << "\t" << endl;
//}
//
//Samochod_Osobowy& Samochod_Osobowy::operator=(const Samochod_Osobowy& obj)
//{
//	pojemnosc_bagaznika = obj.pojemnosc_bagaznika;
//	return *this;
//}
//Samochod_Osobowy& Samochod_Osobowy::operator+(const Samochod_Osobowy& obj)
//{
//	pojemnosc_bagaznika = pojemnosc_bagaznika + obj.pojemnosc_bagaznika;
//	return *this;
//}
//Samochod_Osobowy& Samochod_Osobowy::operator+(const Samochod_Ciezarowy& obj)
//{
//	cout << "osobowy+ciezarowy" << endl;
//	pojemnosc_bagaznika = pojemnosc_bagaznika + obj.ladownosc;
//	return *this;
//}
//Samochod_Osobowy& Samochod_Osobowy::operator=(const Samochod_Ciezarowy& obj)
//{
//	cout << "osobowy=ciezarowy" << endl;
//	pojemnosc_bagaznika = obj.ladownosc;
//	return *this;
//}
//
////konstruktor domyslny
//Samochod_Osobowy::Samochod_Osobowy() :Samochod()
//{
//	pojemnosc_bagaznika = 10;
//	typ_sylwetki = 'K';
//}
////konstruktor kopiujacy
//Samochod_Osobowy::Samochod_Osobowy(Samochod_Osobowy* stary_samochod_osobowy) :Samochod(stary_samochod_osobowy)
//{
//	pojemnosc_bagaznika = stary_samochod_osobowy->pojemnosc_bagaznika;
//	typ_sylwetki = stary_samochod_osobowy->typ_sylwetki;
//}
////konstruktor z argumentami
//Samochod_Osobowy::Samochod_Osobowy(double pojemnosc, char sylwetka, string name, double price, string engine) :
//	Samochod(name, price, engine)
//{
//	pojemnosc_bagaznika = pojemnosc;
//	typ_sylwetki = sylwetka;
//}
//Samochod_Osobowy::Samochod_Osobowy(string name) :
//	Samochod(name, 0, "B")
//{
//	pojemnosc_bagaznika = 10;
//	typ_sylwetki = 'K';
//}
//
//void Samochod_Ciezarowy::wypiszF(FILE* outFile)
//{
//	Samochod::wypiszF(outFile);
//	fprintf(outFile, "%lf %d\n", ladownosc, liczba_kol);
//}
////getery
//double Samochod_Ciezarowy::get_ladownosc()
//{
//	return ladownosc;
//}
//int Samochod_Ciezarowy::get_liczba_kol()
//{
//	return liczba_kol;
//}
////setery
//void Samochod_Ciezarowy::set_ladownosc(double value)
//{
//	ladownosc = value;
//}
//void Samochod_Ciezarowy::set_liczba_kol(int value)
//{
//	liczba_kol = value;
//}
//void Samochod_Ciezarowy::wypisz()
//{
//	Samochod::wypisz();
//	cout << ladownosc << "\t" << liczba_kol << "\t" << endl;
//}
//Samochod_Ciezarowy& Samochod_Ciezarowy::operator=(const Samochod_Ciezarowy& obj)
//{
//	ladownosc = obj.ladownosc;
//	liczba_kol = obj.liczba_kol;
//	return *this;
//}
//Samochod_Ciezarowy& Samochod_Ciezarowy::operator+(const Samochod_Ciezarowy& obj)
//{
//	ladownosc = ladownosc + obj.ladownosc;
//	liczba_kol = liczba_kol + obj.liczba_kol;
//	return *this;
//}
//Samochod_Ciezarowy& Samochod_Ciezarowy::operator=(const Samochod_Osobowy& obj)
//{
//	cout << "ciezarowy=osobowy" << endl;
//	ladownosc = obj.pojemnosc_bagaznika;
//	return *this;
//
//}
//Samochod_Ciezarowy& Samochod_Ciezarowy::operator+(const Samochod_Osobowy& obj)
//{
//	cout << "ciezarowy+osobowy" << endl;
//	ladownosc = ladownosc + obj.pojemnosc_bagaznika;
//	return *this;
//
//}
//
//class Operat {
//public:
//	double dodawanie(double a, double b) {
//		a += b;
//		cout << "dodawanie" << endl;
//		return a;
//	}
//	double odejmowanie(double a, double b) {
//		a = a- b;
//		cout << "odejmowanie" << endl;
//		return a;
//	}
//	double mnozenie(double a, double b) {
//		a = a * b;
//		cout << "mnozenie" << endl;
//		return a;
//	}
//	double dzielenie(double a, double b) {
//		a = a / b;
//		cout << "dzielenie" << endl;
//		return a;
//	}
//	Operat() {
//
//	}
//};
//
//double (Operat::* wsk[4])(double,double);
//
//double ewaluacja(double liczba_1, double liczba_2) {
//	Operat obiekt;
//	double suma = 0;
//	srand((unsigned)time(NULL));
//	for (int i=0; i< 4;i++) {
//		int x = rand() % 4;
//		double wynik = (obiekt.*wsk[x])(liczba_1,liczba_2);
//		suma += wynik;
//	}
//	return suma;
//}
//
////konstruktor domyslny
//Samochod_Ciezarowy::Samochod_Ciezarowy() :Samochod()
//{
//	ladownosc = 20;
//	liczba_kol = 6;
//}
////konstruktor kopiujacy
//Samochod_Ciezarowy::Samochod_Ciezarowy(Samochod_Ciezarowy* stary_samochod_ciezarowy) :Samochod(stary_samochod_ciezarowy)
//{
//	ladownosc = stary_samochod_ciezarowy->ladownosc;
//	liczba_kol = stary_samochod_ciezarowy->liczba_kol;
//}
////konstruktor z argumentami
//Samochod_Ciezarowy::Samochod_Ciezarowy(double ladownosc_s, int kola, string name, double price, string engine)
//	:Samochod(name, price, engine)
//{
//	ladownosc = ladownosc_s;
//	liczba_kol = kola;
//}
//Samochod_Ciezarowy::Samochod_Ciezarowy(string name)
//	: Samochod(name, 0, "B")
//{
//	ladownosc = 20;
//	liczba_kol = 6;
//}
//
//string znajdz_slowo(string linia, int numer)
//{
//	int i = 0;
//	int wystapienie_spacji = 0;
//	int start_slowa = 0;
//	int koniec_slowa = 0;
//	while (i < linia.length())
//	{
//		if (linia[i] == ' ')
//		{
//			wystapienie_spacji++;
//		}
//		if (wystapienie_spacji == numer - 1 && start_slowa == 0)
//		{
//			start_slowa = i;
//		}
//		if (wystapienie_spacji == numer)
//		{
//			koniec_slowa = i;
//			break;
//		}
//		i++;
//	}
//	if (koniec_slowa != 0) {
//		return linia.substr(start_slowa + 1, koniec_slowa - start_slowa - 1);
//	}
//	else {
//		return linia.substr(start_slowa + 1, linia.length() - start_slowa - 1);
//	}
//}
//
//Samochod_Ciezarowy* wczytaj_ciezarowke(string linia)
//{
//	Samochod_Ciezarowy* ciezarowka;
//	double ladownosc = stod(znajdz_slowo(linia, 2));
//	int kola = stoi(znajdz_slowo(linia, 3));
//	string name = znajdz_slowo(linia, 4);
//	double price = stod(znajdz_slowo(linia, 5));
//	string engine = znajdz_slowo(linia, 6);
//	ciezarowka = new Samochod_Ciezarowy(ladownosc, kola, name, price, engine);
//	return ciezarowka;
//}
//
//Samochod_Osobowy* wczytaj_osobowy(string linia)
//{
//	Samochod_Osobowy* osobowy;
//	double pojemnosc_bagaznika = stod(znajdz_slowo(linia, 2));
//	char typ_sylwetki = znajdz_slowo(linia, 3)[0];
//	string name = znajdz_slowo(linia, 4);
//	double price = stod(znajdz_slowo(linia, 5));
//	string engine = znajdz_slowo(linia, 6);
//	osobowy = new Samochod_Osobowy(pojemnosc_bagaznika, typ_sylwetki, name, price, engine);
//	return osobowy;
//}
//
//Samochod* wczytaj_samochod(string linia)
//{
//	if (linia[0] == 'C')
//	{
//		return wczytaj_ciezarowke(linia);
//	}
//	else
//	{
//		return wczytaj_osobowy(linia);
//	}
//}
//
//int main() {
//	cout << "Autorka Dorota Siciak. Program sumuje obiekty samochodow \n\n" << endl;
//	Samochod* glowa = NULL;
//	Samochod* nowy;
//	ifstream file("samochody_osobowe.txt");
//	string wiersz;
//	while (getline(file, wiersz))
//	{
//		if (glowa == NULL)
//		{
//			glowa = wczytaj_samochod(wiersz);
//		}
//		else
//		{
//			nowy = wczytaj_samochod(wiersz);
//			nowy->nast = glowa;
//			glowa = nowy;
//		}
//	}
//	file.close();
//
//	Samochod_Osobowy A1("A1"), A2("A2");
//	Samochod_Ciezarowy B1("B1"), B2("B2");
//
//	cout << "Test operatorow konwersji" << endl;
//	A2 = B1 + A1;
//	B2 = A1 + B2;
//
//	A2.wypisz();
//	B2.wypisz();
//	//operatory ktore sa w uzyciu w kolejnosci:
//	//ciezarowy+osobowy
//	//osobowy = ciezarowy
//	//osobowy + ciezarowy
//	//ciezarowy = osobowy
//	//lab14 poziom2
//	wsk[0] = &Operat::dodawanie;
//	wsk[1] = &Operat::odejmowanie;
//	wsk[2] = &Operat::mnozenie;
//	wsk[3] = &Operat::dzielenie;
//	for (int i=0; i < 5; i++) {
//		cout << "Podaj 2 liczby rzeczywiste:\n";
//		double a;
//		double b;
//		cin >> a;
//		cin >> b;
//		double wynik=ewaluacja(a, b);
//		cout << "Oto wynik ewaluacji:" << wynik;
//	}
//	return 0;