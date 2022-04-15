#include<cstdio>
#include<iostream>
#include<cassert>
#include<cfloat>
#include<ctime>
#include<math.h>

#define N 6

using namespace std;

template<typename T>
class Konten
{
	enum { ssize = 100 };
	T stack[ssize];
	int top;
public:
	Konten() : top(0) {}
	void push(T i)
	{
		assert(top < ssize);  stack[top++] = i;
	};
	T pop()
	{
		assert(top > 0);  return stack[--top];
	};
	int rozmiar() { return top; };

	class iterator
	{
		Konten& s;
		int index;
	public:
		iterator(Konten& is) : s(is), index(0) {};
		iterator(Konten& is, bool) : s(is), index(s.top) {};
		T operator++()   // Prefix
		{
			assert(index < s.top);
			return s.stack[++index];
		};
		T operator++(int)   // Postfix
		{
			assert(index < s.top);
			return s.stack[index++];
		};
		T& operator*() const { return s.stack[index]; };
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

template <typename T>
class pomiary {
public:
	Konten<T> przed;
	Konten<T> po;
};

double randdouble()//funkcja generujaca liczby typu double z przedzialu <0,100)
{
	double liczba = rand() / (double(RAND_MAX) + 10);
	return liczba + (rand() % 100);
}

template<typename T>
void wypisz_kontener(T start, T end) {
	while (start != end) {
		cout << *start << endl;
		start++;
	}
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
		*i1 *= *i1;
		i1++;
	}
}

template<typename T>
double policz_s(T start, T koniec) {
	double suma = 0;
	while (start != koniec) {
		suma += *start;
		start++;
	}
	double s = sqrt(suma / (N - 1));
	return s;
}


template<typename T>
class Kalkulator {
	T value;
public:
	Kalkulator() {
	};
	template<typename T>
	static void testtStudenta(typename Konten<pomiary<T>>::iterator& pierwszy, typename Konten<pomiary<T>>::iterator& drugi) {
		typename Konten<pomiary<double>>::iterator help = pierwszy;
		typename Konten<pomiary<double>>::iterator help2 = pierwszy;
		T min = DBL_MAX;
		T max = DBL_MIN;
		double testy[N] = { 0 };
		int l = 0;
		while (pierwszy != drugi) {
			pomiary<double>pom = *pierwszy;
			roznicuj1(pom.przed.begin(), pom.przed.end(), pom.po.begin());
			double suma = 0;
			for (int i = 0;i < N;i++) {
				suma += *pom.przed.begin();
				pom.przed.begin()++;
			}
			double d = suma / N;
			//s
			roznicuj2(pom.przed.begin(), pom.przed.end(), d);
			do_kwadratu(pom.przed.begin(), pom.przed.end());
			double s = policz_s(pom.przed.begin(), pom.przed.end());
			testy[l] = d / (s / (sqrt(N)));
			pierwszy++;
			l++;
		}
		int i_min = 0;
		int i_max = 0;
		for (int i = 0; i < N; i++) {
			if (testy[i]>max) {
				max = testy[i];
				i_max = i;
			}
			if (testy[i]<min) {
				min = testy[i];
				i_min = i;
			}
		}
		cout << "Wartosc T najmniejsza  " << min << endl;
		cout << "Wartosc T najwieksza  " << max << endl;
		for (int i = 0; i < i_min; i++) {
			help++;
		}
		for (int i = 0; i < i_max; i++) {
			help2++;
		}
		pierwszy = help;
		drugi = help2;
	}
};

int main(){
	srand((unsigned int)time(NULL));
	Konten<pomiary<double>>konten_1;
	pomiary<double>pomoc;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			pomoc.przed.push(randdouble());
			pomoc.po.push(randdouble());
		}
		wypisz_kontener(pomoc.przed.begin(),pomoc.przed.end());
		wypisz_kontener(pomoc.po.begin(),pomoc.po.end());
		konten_1.push(pomoc);
	}
	Kalkulator<double>calc;
	Konten<pomiary<double>>::iterator poczatek = konten_1.begin();
	Konten<pomiary<double>>::iterator koniec = konten_1.end();
	calc.testtStudenta<double>(poczatek, koniec);
}
