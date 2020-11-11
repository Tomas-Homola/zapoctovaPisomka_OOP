#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::cout;
using std::endl;

//Zadanie začína pod definíciou konštruktora triedy Date
class Date {
private:
	int d = 0, m = 0, y = 0;
public:
	Date() {};
	Date(int D, int M, int Y) :d(D), m(M), y(Y) {};
	Date& fromString(std::string dtext);
	std::string toString()
	{
		return std::string(std::to_string(d) + "." + std::to_string(m) + "." + std::to_string(y));
	};
};

Date& Date::fromString(std::string dtext)
{
	size_t pos = 0;
	std::string token;
	int date[3] = { 0,0,0 };
	int counter = 0;
	std::string delimiter = ".";

	while ((pos = dtext.find(".")) != std::string::npos)
	{

		token = dtext.substr(0, pos);
		date[counter] = std::stoi(token);
		dtext.erase(0, pos + delimiter.length());
		counter++;
	}
	d = date[0];
	m = date[1];
	y = std::stoi(dtext);
	return *this;
}

//1. Vytvorte triedy Employee a Manager podľa nasledovného objektového návrhu (obe musia spĺňať data hiding):


/*
Trieda Employee bude mať premenné:
-   priezvisko zamestnanca
-	dátum nástupu do zamestnania (premenná bude triedy Date)
-	neceločíselná hodnota výplaty v EUR
a metódy:
-	prázdny konštruktor, ktorý nastaví defaultne „nulové“ hodnoty
-	konštruktor s parametrami
-	metódy na pristúp a nastavenie premenných
*/

class Employee
{
private: // asi mozno protected
	string priezvisko;
	Date nastup;
	double vyplata;

public:
	Employee();
	Employee(string priezvisko, Date nastup, double vyplata);

	string getPriezvisko() { return priezvisko; }
	Date getNastup() { return nastup; }
	double getVyplata() { return vyplata; }

	void setPriezvisko(string nPriezvisko) { priezvisko = nPriezvisko; }
	void setNastup(string nastup) { this->nastup.fromString(nastup); }
	void setVyplata(double nVyplata) { vyplata = nVyplata; }


};

Employee::Employee()
{
	priezvisko = "N/A";
	nastup.fromString("0.0.0");
	vyplata = -1;
}

Employee::Employee(string priezvisko, Date nastup, double vyplata)
{
	this->priezvisko = priezvisko;
	this->nastup = nastup;
	this->vyplata = vyplata;
}

/*
Trieda Manager bude dediť triedu Employee a bude mať premenné:
-	celočíslena hodnota počtu zamestnacov v tíme
a metódy:
-	prázdny konštruktor, ktorý nastaví defaultne „nulové“ hodnoty
-	konštruktor s parametrami schopný nastaviť aj premenné rodičovskej triedy
-	metódy na pristúp a nastavenie premenných
-	metódu print, ktorá vypíše všetky dostupné údaje
*/

class Manager : public Employee
{
private:
	int employees;
public:
	Manager() : Employee() { employees = -1; }
	Manager(string priezvisko, Date nastup, double vyplata, int employees) : Employee(priezvisko, nastup, vyplata) { this->employees = employees; }

	int getEmployees() { return employees; }

	void setEmployees(int nEmployees) { this->employees = nEmployees; }

	void printInfo();
};

void Manager::printInfo()
{
	cout << "Priezvisko: " << getPriezvisko() << ", nastupil: " << getNastup().toString() << ", ma vyplatu: " << getVyplata() << " EUR, pocet zamestnancov: " << getEmployees() << endl;
}


void changeNumberOfEmps(Manager* m, int newNumberOfEmps)
{
	//2. zavolajte funkciu ktorá zmení hodnotu počtu zamestnacov v tíme pre objekt m
	m->setEmployees(newNumberOfEmps);
}

int main()
{
	std::cout << "Kolko zaznamov sa ma nacitat? (max 3)" << std::endl;
	int n = 0;

	//3. do premennej n načítajte hodnotu z konzoly
	std::cin >> n;

	//4. dynamicky alokujte pole pre n objektov triedy Manager do premennej managers
	Manager* managers;
	managers = new Manager[n];

	//5. zabezpecte aby nasledujúci riadok nevypisoval chybu
	std::fstream textfile;
	// pridany #include <fstream>

	//6. do premennej textfile otvorte súbor dataManagers.txt na čítanie

	textfile.open("dataManagers.txt", std::ios::in);

	if (textfile.is_open() == false)
	{
		std::cout << "Subor sa nepodarilo otvorit!" << std::endl;
	}

	//7. vo vnútri v cykle naplňte do tmp premennych hodnoty zo subora
	// a tie následne nastavte do objektov v poli managers
	for (int i = 0; i < n; i++)
	{
		std::string tmpName;
		std::string tmpStarthDate;
		std::string tmpSalary;
		std::string tmpNumberOfEmps;

		textfile >> tmpName;
		textfile >> tmpStarthDate;
		textfile >> tmpSalary;
		textfile >> tmpNumberOfEmps;

		managers[i].setPriezvisko(tmpName);
		managers[i].setNastup(tmpStarthDate);
		managers[i].setVyplata(std::stod(tmpSalary));
		managers[i].setEmployees(std::stoi(tmpNumberOfEmps));

	}

	for (int i = 0; i < n; i++)
	{
		managers[i].printInfo();
	}

	//8. upravte funkciu changeNumberOfEmps aby nepracovala s kópiou posledného objektu v poli managers, 
	//ale aby priamo pristupovala k objektu
	changeNumberOfEmps(&managers[n - 1], 12);

	for (int i = 0; i < n; i++)
	{
		managers[i].printInfo();
	}

	textfile.close();
	return 0;
}