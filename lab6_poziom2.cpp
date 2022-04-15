//Dorota Siciak

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

template<class T>
struct sortowanie_listy
{
	bool operator()(const T &x, const T &y) const
	{
		return x.size() > y.size();
	}
	;
	typedef T first_argument_type;
	typedef T second_argument_type;
	typedef bool result_type;
};

class Mikser2: public list<set<string>>
{
public:
	~Mikser2()
	{
	}
	Mikser2()
	{
		while (!empty())
		{
			back().clear();
			pop_back();
		}

	}
	Mikser2(const char *nazwa_pliku)
	{
		open(nazwa_pliku);
	}

	void open(const char *nazwa_pliku)
	{
		ifstream is(nazwa_pliku);
		if (is.is_open())
		{
			string linia;
			while (getline(is, linia))
			{
				set<string> zestaw_wyrazow;
				string wyraz;
				istringstream iss(linia);
				while (iss >> wyraz)
				{
					zestaw_wyrazow.insert(wyraz);
				}
				push_back(zestaw_wyrazow);
			}
			is.close();
		}
		else
		{
			cout << "Blad otwarcia pliku " << nazwa_pliku << endl;
		}
	}
	template<typename T>
	class Domieszka: T
	{
	public:
		virtual void write_set(set<string> &zestaw_slow, fstream &fs)
		{
			{
				fs << zestaw_slow.size() << ": ";
				T::write_set(zestaw_slow, fs);
			}
		}
		;
	};
	void write(const char *nazwa_pliku)
	{
		Domieszka<Mikser2> mikser_z_domieszka;
		fstream fs;
		fs.open(nazwa_pliku, ios::out);
		if (fs.good())
		{
			while (!empty())
			{
				set<string> zestaw_slow = front();
				mikser_z_domieszka.write_set(zestaw_slow, fs);
				pop_front();
			}
			fs.close();
		}

	}
	void execute()
	{
		sort(sortowanie_listy<set<string>>());
	}
	void write_set(set<string> &zestaw_slow, fstream &fs)
	{
		for (set<string>::iterator it = zestaw_slow.begin(); it != zestaw_slow.end(); it++)
		{
			fs << *it << " ";
		}
		fs << endl;

	}

};

int main()
{
	Mikser2 lista;
	lista.open("quovadis.txt");
	lista.execute();
	lista.write("quovadis_po_zmianach.txt");
	cout << "Koniec" << endl;

	return 0;
}
