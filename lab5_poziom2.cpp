#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<limits>
#include <iomanip>
#include<exception>
#include<math.h>

using namespace std;

class Bazowe_Cechy {
public:
	static const bool _jest_liczba = false;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const int _dolna_granica_przedzialu = 0;
	static const int _gorna_granica_przedzialu = 0;
	static constexpr double _pinty = 0.0;
	static const int _liczb_po_przecinku = 0;
	static const bool _jest_pierwsza = false;
	static const bool _czy_bije = false;

};

template<typename T>
class Cechy : public Bazowe_Cechy {
public:
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 0; };
	static const double precyzja() { return 0; };
};

class temperatura_wody {
	double t;
public:
	temperatura_wody(double temp = 50) : t(temp) {};
	double operator()() { return t; };
	temperatura_wody& operator=(double temp) { t = temp; return *this; };
};

template<>
class Cechy<temperatura_wody> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 100; };
};

class kostka_do_gry {
	int n;
public:
	kostka_do_gry(int num = 1) : n(num) {};
	int operator()() { return n; };
	kostka_do_gry& operator=(int num) { n = num; return *this; };
};

template<>
class Cechy<kostka_do_gry> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 1;
	static const int _gorna_granica_przedzialu = 6;
};

//---------------------------------------------------------------------------------------------------
class minuta_dnia {
	int ktora_minuta;
public:
	minuta_dnia(int min = 15) : ktora_minuta(min) //{};
	{
		if (min < 1 || min>1440) ktora_minuta = 15; else ktora_minuta = min;
	}
	int operator ()() { return ktora_minuta; }
	minuta_dnia& operator = (int min) {ktora_minuta = min; return *this; }
	friend std::ostream& operator << (std::ostream& os, const minuta_dnia& minuta);
};

template<>
class Cechy<minuta_dnia> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 1;
	static const int _gorna_granica_przedzialu = 1440;
};

ostream& operator << (ostream& os, const minuta_dnia& minuta) {
	os << std::fixed << std::setprecision(Cechy<minuta_dnia>::_liczb_po_przecinku) << minuta.ktora_minuta;
	return os;
}

class uderzenia_zegara
{
	double uderzenia;
public:
	uderzenia_zegara(double value = 22.8) : uderzenia(value)
	{
		if ((value < 0.8 || value>22.8) && (round((value - 0.8)/2)*2 != value-0.8 || (value - 0.8) != 0)) uderzenia = 22.8; else uderzenia = value;
	}
	double operator ()() { return uderzenia; }
	uderzenia_zegara& operator = (double wartosc) { uderzenia = wartosc; return *this; }
	friend std::ostream& operator << (std::ostream& os, const uderzenia_zegara& uderzenia);
};

template<>
class Cechy<uderzenia_zegara> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const double dolna_granica_przedzialu() { return 0.8; };
	static const double gorna_granica_przedzialu() { return 22.8; };
	static const bool _czy_bije = true;
	static const int _liczb_po_przecinku = 1;
};

ostream& operator << (ostream& os, const uderzenia_zegara& uderzenia) {
	os << std::fixed << std::setprecision(Cechy<uderzenia_zegara>::_liczb_po_przecinku) << uderzenia.uderzenia;
	return os;
}

class ilosc_piwa
{
	double litry;
public:
	ilosc_piwa(double value = 0.568) : litry(value)
	{
		cout << "kons"<< std::fixed << std::setprecision(4)  << value<< "  "<< abs(round(value / 0.568) * 0.568 - value)  << endl;
		if (value < 0.568 || abs(round(value/0.568)*0.568-value)>0.001) litry = 0.568; else litry=value;
	}
	double operator ()() { return litry; }
	ilosc_piwa& operator = (double wartosc) { litry = wartosc; return *this; }
	friend std::ostream& operator << (std::ostream& os, const ilosc_piwa& litry);
};

template<>
class Cechy<ilosc_piwa> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = false;
	static const double dolna_granica_przedzialu() { return 0.568; };
	static const double gorna_granica_przedzialu() { return LONG_MAX; };
	static constexpr double _pinty = 0.568;
	static const int _liczb_po_przecinku = 3;
};

ostream& operator << (ostream& os, const ilosc_piwa& litry) {
	os << std::fixed << std::setprecision(Cechy<ilosc_piwa>::_liczb_po_przecinku) << litry.litry;
	return os;
}

bool czy_pierwsza(int value) {
	if (value < 2) {
		return false;
	}
	for (int i = 2; i < value - 1; i++)
		if (value % i == 0)
			return false;
	return true;
}

class liczba_pierwsza
{
private:
	int liczba;
public:
	liczba_pierwsza(int value = 17) :liczba(value)
	{
		if (!czy_pierwsza(value)) liczba = 17; else liczba = value;
	}
	int operator ()() { return liczba; }
	liczba_pierwsza& operator = (int wartosc) { liczba = wartosc; return *this; }
	friend std::ostream& operator << (std::ostream& os, const liczba_pierwsza& liczba);
};

template<>
class Cechy<liczba_pierwsza> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 2;
	static const int _gorna_granica_przedzialu = 1000000;
	static const bool _jest_pierwsza = true;

};

ostream& operator << (ostream& os, const liczba_pierwsza& liczba) {
	os << std::fixed << std::setprecision(Cechy<liczba_pierwsza>::_liczb_po_przecinku) << liczba.liczba;
	return os;
}


class Przepelnienie : public exception {
	char opis[100];
public:
	//	Przepelnienie(const char* o) { strcpy_s(opis, o); }
	Przepelnienie(const char* o) { strcpy(opis, o); }
	const char* what() const throw() { return opis; };
};
class BrakDanych : public exception {
	char opis[100];
public:
	//	BrakDanych(const char* o) { strcpy_s(opis, o); }
	BrakDanych(const char* o) { strcpy(opis, o); }
	const char* what() const throw() { return opis; };
};


template<typename T, int rozmiar, class _Cechy = Cechy<T>>
class SzablonStosu {
	T stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	SzablonStosu() : top(0) {}
	void push(const T& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	void push(int i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja wartoœci przekazanej do zapisu
		if (Cechy<T>::_jest_liczba && Cechy<T>::_jest_liczba_calkowita) {
			if (Cechy<T>::_nalezy_do_przedzialu) {
				if ((Cechy<T>::_dolna_granica_przedzialu <= i) && (i <= Cechy<T>::_gorna_granica_przedzialu)) {
					if (Cechy<T>::_jest_pierwsza) {
						if (czy_pierwsza(i)) {
							stos[top++] = i;
						}
					}
					else {
						stos[top++] = i;
					}
				}
			}
			else
				stos[top++] = i;
		}
	}
	void push(double i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja wartoœci przekazanej do zapisu
		if (Cechy<T>::_jest_liczba && !Cechy<T>::_jest_liczba_calkowita) {
			if (Cechy<T>::_nalezy_do_przedzialu) {
				if ((Cechy<T>::dolna_granica_przedzialu() <= i) && (i <= Cechy<T>::gorna_granica_przedzialu())) {
					if (Cechy<T>::_pinty > 0) {
						if (abs((round(i / Cechy<T>::_pinty) * Cechy<T>::_pinty)-i)<0.001) {
							stos[top++] = i;
						}
					}
					else if (Cechy<T>::_czy_bije) {
						cout << i << " "<< (i >= 0.8 && i <= 22.8)<< " " << (abs((round((i - 0.8) / 2) * 2) - (i - 0.8))<0.001) << " " <<(abs(i - 0.8) < 0.001) << endl;
						if ((i >= 0.8 && i <= 22.8) &&((abs((round((i - 0.8) / 2) * 2) - (i - 0.8)) < 0.001) || (i - 0.8) == 0)) {
							stos[top++] = i;
						}
					}
					else {
						stos[top++] = i;
					}

				}
			}
			else
				stos[top++] = i;
		}
	}
	T pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());

		return stos[--top];
	}
	void wypisz()
	{
		for (int i = 0; i < top; i++)
		{
			cout << stos[i] << endl;
		}
	}
};

class Stos2
{
	static const int rozmiar = 10;
protected:
	double stos[rozmiar];
	int top;
public:
	int zajetosc()
	{
		return top;
	}
	;
	Stos2() :
		top(0)
	{
	}
	virtual void push(const double& i)
	{
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	virtual double pop()
	{
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());
		return stos[--top];
	}
};

template <typename T>
class Domieszka_pierwsza : public T
{
public:
	double pop()
	{
		cout << "Ilosc elementow : " << T::zajetosc();
		double wartosc = T::pop();
		cout << endl << "Pobierany element: " << std::fixed << std::setprecision(3) << wartosc << endl;
		return wartosc;
	}
};

template <typename T>
class Domieszka_druga : public T
{
private:
	double suma_stosu = 0;
public:
	double pop()
	{
		double wartosc = T::pop();
		suma_stosu -= wartosc;
		cout << "Suma wartosci na stosie: " << std::fixed << std::setprecision(3) << abs(suma_stosu) << endl;
		return wartosc;
	}
	void push(double wartosc) {
		T::push(wartosc);
		suma_stosu += wartosc;
		cout << "Suma wartosci na stosie: " << std::fixed << std::setprecision(3) << abs(suma_stosu) << endl;
	}
};

int main() {
	SzablonStosu<string, 5> K1;
	SzablonStosu<temperatura_wody, 10> K2;
	SzablonStosu<kostka_do_gry, 10> K3;


	// zape³nianie stosu
	ifstream fi("qv-lab4.txt");
	string s;
	try {
		K1.push("Henryk");
		K1.push("Sienkiewicz");
		while (fi) {
			fi >> s;
			K1.push(s);
			fi.seekg(ios::beg);
			fi.clear();
			cout << '*';
		};
	}
	catch (Przepelnienie& e) {
		cout << "K1 gotowy: " << e.what() << endl;
	};
	cout << "Danych na stosie K1: " << K1.zajetosc() << endl;

	K2.push(temperatura_wody());
	K2.push(temperatura_wody(36.6));
	K2.push(40);
	K2.push(71.2);
	cout << "Danych na stosie K2: " << K2.zajetosc() << endl;

	K3.push(kostka_do_gry(3));
	K3.push(kostka_do_gry());
	K3.push(4);
	K3.push(6);
	K3.push(10);
	cout << "Danych na stosie K3: " << K3.zajetosc() << endl;

	// opró¿nianie stosu
	try {
		while (true)
			K1.pop();
	}
	catch (BrakDanych& e) {
		cout << "K1 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K2.pop();
	}
	catch (BrakDanych& e) {
		cout << "K2 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K3.pop();
	}
	catch (BrakDanych& e) {
		cout << "K3 pusty: " << e.what() << endl;
	}

	SzablonStosu<minuta_dnia, 10> K4;

	K4.push(14);
	K4.push(16);
	K4.push(1550); // pominiêty
	cout << "K4 wypisz " << endl;
	K4.wypisz();

	SzablonStosu<uderzenia_zegara, 10> K5;
	K5.push(0.8);
	K5.push(21.8); // pominiêty
	K5.push(2.8);
	cout << "K5 wypisz " << endl;
	K5.wypisz();

	SzablonStosu<ilosc_piwa, 10> K6;
	K6.push(3.976);
	K6.push(1.709); // pominiêty
	K6.push(ilosc_piwa(1.704));
	cout << "K6 wypisz " << endl;
	K6.wypisz();

	SzablonStosu<liczba_pierwsza, 10> K7;
	K7.push(3);
	K7.push(33); // pominiêty
	K7.push(127);
	cout << "K7 wypisz " << endl;
	K7.wypisz();

	//poziom 2
	cout << "------------poziom 2-------------" << endl;
	Stos2 stos_dwa;

	stos_dwa.push(11);
	stos_dwa.push(33);
	stos_dwa.push(22);
	stos_dwa.push(44);
	try {
		while (true)
			cout << "zdejmowanie ze stosu2: " << stos_dwa.pop() << endl;
	}
	catch (BrakDanych& e) {
		cout << "stos_dwa pusty: " << e.what() << endl;
	}

	Domieszka_druga<Domieszka_pierwsza<Stos2>> stos_z_domieszkami;
	cout << "Stos2 push" << endl;
	stos_z_domieszkami.push(1.1);
	stos_z_domieszkami.push(1.2);
	stos_z_domieszkami.push(1.3);
	stos_z_domieszkami.push(1.4);
	cout << "Stos2 pop" << endl;
	stos_z_domieszkami.pop();
	stos_z_domieszkami.pop();
	stos_z_domieszkami.pop();
	stos_z_domieszkami.pop();

	return 0;
}
