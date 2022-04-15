#include<cstdio>
#include<iostream>
#include<cassert>
#include<cfloat>
#include<ctime>
#include<math.h>

#define N 50

using namespace std;

template<typename T>
class Element {
public:
	T wartosc;
	Element* nast;
	Element(T value) {
		wartosc = value;
	}
};

template<typename Obj>
class Stos {
public:
	Element<Obj>* poczatek = NULL;
	void push(Obj value) { //poloz na stos
		Element<Obj>*  obiekt = new Element<Obj>(value);
		if (poczatek == NULL) {
			poczatek = obiekt;
		}
		else {
			Element<Obj>* zapamietaj_poczatek = poczatek;
			while (poczatek->nast != NULL) {
				poczatek = poczatek->nast;
			}
			poczatek->nast = obiekt;
			poczatek = zapamietaj_poczatek;
		}
	}
	//Obj* get() { //zdejmuje ze stosu
	//	Obj* zwracany = NULL;

	//	if (poczatek == NULL) { // brak elementów
	//		zwracany = NULL;
	//	}
	//	else if (poczatek->nast == NULL) {// jeden element
	//		zwracany = poczatek;
	//		poczatek = NULL;
	//	}
	//	else { // co najmniej dwa elementy
	//		Obj* wrk_poczatek = poczatek;
	//		while (wrk_poczatek->nast != NULL && wrk_poczatek->nast->nast != NULL) {
	//			wrk_poczatek = wrk_poczatek->nast;
	//		}
	//		zwracany = wrk_poczatek->nast;
	//		wrk_poczatek->nast = NULL;
	//	}
	//	return zwracany;
	//}
	Element<Obj>* top() {
		Element<Obj>* zapamietaj_poczatek = poczatek;
		Element<Obj>* zwracany = NULL;

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
	Stos() {
	}
	~Stos() {
		if (poczatek != NULL) {
			while (poczatek->nast != NULL) {
				Element<Obj>* tmp_poczatek = poczatek;
				poczatek = poczatek->nast;
				delete tmp_poczatek;
			}
			delete poczatek;
		}
	}
	class iterator
	{
		Stos& s;
		Element<Obj>* index;
	public:
		iterator(Stos& is) : s(is), index(is.poczatek) {};
		iterator(Stos& is, bool) : s(is) {
			Element<Obj>* wsk = s.poczatek;			while (wsk->nast != NULL) {
				wsk = wsk->nast;
			}
			index = wsk;
		};
		int size(iterator i1, iterator i2) {
			int ile = 0;
			while (i1!=i2) {
				i1++;
				ile++;
			}
			return ile;
		}
		Obj operator++()   // Prefix
		{
			index=index->nast;
			return index->wartosc;
		};
		Obj operator++(int)   // Postfix
		{
			index = index->nast;
			return index->wartosc;
		};
		Obj& operator*() const { return index->wartosc; };
		iterator& operator=(const iterator& rv)
		{
			s = rv.s;
			index = rv.index;
			return *this;
		}
		bool operator!=(const iterator& i2) {
			if (index != i2.index)
				return true;
			return false;
		}
	};
	iterator begin() { return iterator(*this); };
	iterator end() { return iterator(*this, true); };

	friend class iterator;
};


double randdouble()//funkcja generujaca double z przedzialu <0,10)
{
	double liczba = rand() / (double(RAND_MAX) + 10);
	return liczba + (rand() % 10);
}

template<typename T>
void roznicuj1(T i1, T i2, T i3) {
	while (i1 != i2) {
		*i1 = *i1 - *i3;
		i1++;
		i3++;
	}
}

template<typename T>
void roznicuj2(T i1, T i2, double d) {
	while (i1 != i2) {
		*i1 = *i1 - d;
		i1++;
	}
}

template<typename T>
void do_kwadratu(T i1, T i2) {
	while (i1 != i2) {
		*i1 *=*i1;
		i1++;
	}
}

template<typename T>
void wypisz_kontener(T start,T end) {
	while (start != end) {
		cout << *start << endl;
		start++;
	}
}

template<typename T>
double policz_s(T start, T koniec) {
	double suma = 0;
	while (start!=koniec) {
		suma += *start;
		start++;
	}
	double s = sqrt(suma/(N-1));
	return s;
}

int main() {
	srand((unsigned int)time(NULL));
	Stos<double>konten_1;
	Stos<double>konten_2;
	for (int i = 0; i < N; i++) {
		konten_1.push(randdouble());
		konten_2.push(randdouble());
	}
	cout << "KONTENER 1" << endl;
	wypisz_kontener(konten_1.begin(),konten_1.end());
	cout << "KONTENER 2" << endl;
	wypisz_kontener(konten_2.begin(),konten_2.end());
	//d
	roznicuj1(konten_1.begin(),konten_1.end(),konten_2.begin());
	double suma = 0;
	for(int i = 0;i < N;i++) {
		suma+=*konten_1.begin();
		konten_1.begin()++;
	}
	double d = suma / N;
	cout << "WARTOSC D " << d << endl;
	//s
	roznicuj2(konten_1.begin(),konten_1.end(),d);
	do_kwadratu(konten_1.begin(),konten_1.end());
	double s =policz_s(konten_1.begin(),konten_1.end());
	cout << "WARTOSC S " << s << endl;
	double t = d / (s / (sqrt(N)));
	cout << "WARTOSC T " << t << endl;
}