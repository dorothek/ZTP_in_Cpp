//Dorota Siciak

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>

using namespace std;

ostream& operator <<(ostream &strumien, list<string> &lista_slow)
{
	strumien << lista_slow.size() << ": ";
	while (!lista_slow.empty())
	{
		strumien << lista_slow.front() << " ";
		lista_slow.pop_front();
	}
	strumien << endl;
	return strumien;
}

// sortowanie rosnaco
bool sortuj_wyrazy_rosnaco(const string &pierwsze, const string &drugie)
{
	unsigned int i = 0;
	while ((i < pierwsze.length()) && (i < drugie.length()))
	{
		if (tolower(pierwsze[i]) < tolower(drugie[i]))
			return true;
		else if (tolower(pierwsze[i]) > tolower(drugie[i]))
			return false;
		++i;
	}
	return (pierwsze.length() < drugie.length());
}

// sortowanie malejaco
bool sortuj_wyrazy_malejaco(const string &pierwsze, const string &drugie)
{
	unsigned int i = 0;
	while ((i < pierwsze.length()) && (i < drugie.length()))
	{
		if (tolower(pierwsze[i]) > tolower(drugie[i]))
			return true;
		else if (tolower(pierwsze[i]) < tolower(drugie[i]))
			return false;
		++i;
	}
	return (pierwsze.length() > drugie.length());
}

template<class T>
struct wieksze
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

class Mikser: public priority_queue<list<string>, vector<list<string>>, wieksze<list<string>>>
{
public:
	Mikser()
	{

	}
	Mikser(const char *nazwa_pliku)
	{
		open(nazwa_pliku);
	}
	~Mikser()
	{

	}
	void open(const char *nazwa_pliku)
	{
		ifstream is(nazwa_pliku);
		if (is.is_open())
		{
			string linia;
			while (getline(is, linia))
			{
				if (linia != "" && linia != "\r")
				{
					list<string> lista_wyrazow;
					string wyraz;
					istringstream iss(linia);
					while (iss >> wyraz)
					{
						lista_wyrazow.push_back(wyraz);
					}
					if (lista_wyrazow.size() > 6)
					{
						lista_wyrazow.sort(sortuj_wyrazy_rosnaco);
//				    	cout<<"rosnaco: "<<lista_wyrazow<<endl;
					}
					else
					{
						lista_wyrazow.sort(sortuj_wyrazy_malejaco);
//				    	cout<<"malejaco: "<<lista_wyrazow<<endl;
					}
					push(lista_wyrazow);
				}
			}
			is.close();
		}
		else
		{
			cout << "Blad otwarcia pliku " << nazwa_pliku << endl;
		}
	}
	void write(const char *nazwa_pliku)
	{
		fstream fs;
		fs.open(nazwa_pliku, ios::out);
		if (fs.good())
		{
			while (!empty())
			{
				list<string> linia = top();
				fs << linia;
				pop();
			}
			fs.close();
		}
	}

};

int main()
{
	Mikser kolejka;
	kolejka.open("mistrz.txt");
	kolejka.write("mistrz_po_zmianach.txt");
	cout << "Koniec" << endl;
	return 0;
}
