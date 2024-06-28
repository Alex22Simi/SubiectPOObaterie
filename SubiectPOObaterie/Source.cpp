#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
//atr constante sunt atribute a caror valoare nu se schimba niciodata
//ele se initializeaza cu o val in constr (se va face initializare in-line)
//CNP

//staticul este un atribut care va avea aceeasi val pt toate obiectele din clasa
//TVA

class PowerBank {
protected:
	const int idBaterie;
	char* numeBaterie;
	int nivelBaterie;
	float pret;
public:
	
	PowerBank():idBaterie(0)
	{
		this->numeBaterie = new char[strlen("Anonim")+1];//alocare spatiu pt atribut
		//1->terminator sir
		strcpy(this->numeBaterie, "Anonim");
		this->nivelBaterie = 0;
		this->pret = 0;
	}
	//punem const la char* pt ca ea primeste o adresa ->vrem sa ramana constanta acea adresa

	PowerBank(int idBaterie, const char* numeBaterie, int nivelBaterie, float pret) :idBaterie(idBaterie)
	{
		this->numeBaterie = new char[strlen(numeBaterie) + 1];//alocare spatiu pt atribut
		//1->terminator sir
		strcpy(this->numeBaterie, numeBaterie);
		this->nivelBaterie = nivelBaterie;
		this->pret = pret;
	}
	//this->pentru atributul din clasa si nu pt parametru

	//getteri & setteri
	int getNivelBaterie()
	{
		return this->nivelBaterie;
	}
	void setNivelBaterie(int nivelBaterie)
	{
		if (nivelBaterie >= 0 && nivelBaterie <= 100)
		{
			this->nivelBaterie = nivelBaterie;
		}
	}

	//constr de copiere
	//se apeleaza atunci cand avem nevoie sa cream un obiect nou pe baza unui constr existent
	//trebuie sa copiem toate atributele din clasa
	PowerBank(const PowerBank &p):idBaterie(p.idBaterie)
	{
		this->numeBaterie = new char[strlen(p.numeBaterie) + 1];//alocare spatiu pt atribut
		//1->terminator sir
		strcpy(this->numeBaterie, p.numeBaterie);
		this->nivelBaterie = p.nivelBaterie;
		this->pret = p.pret;
	}

	//operatorul = 
	//se apeleaza deja intre doua obiecte deja create
	//op = este format din ce scrie in destructor + ce scrie in constructor de copiere + return *this;
	PowerBank &operator=(const PowerBank& p)
	{
		if (this != &p) //sa nu egalam un obiect cu el insususi
		{
			if (this->numeBaterie != NULL)
			{
				delete[] this->numeBaterie;
			}
			this->numeBaterie = new char[strlen(p.numeBaterie) + 1];//alocare spatiu pt atribut
			//1->terminator sir
			strcpy(this->numeBaterie, p.numeBaterie);
			this->nivelBaterie = p.nivelBaterie;
			this->pret = p.pret;
			
		}
		return *this;
	}



	//destructor
	~PowerBank()
	{
		if (this->numeBaterie != NULL)
		{
			delete[] this->numeBaterie;
		}
	}

	//operator <<(operatorul de afisare)
	friend ostream& operator<<(ostream& out, const PowerBank& p)//sa nu se mai apeleze constr de copiere
	{
		out << "Id: " << p.idBaterie << endl;
		out << "Nume: " << p.numeBaterie << endl;
		out << "Procent baterie: " << p.nivelBaterie << "%" <<  endl;
		out << "Pret: " << p.pret << "lei" <<  endl;
		return out;
	}
	//destructorul se apeleaza de cate ori cream un obiect
	


	//operatorii += & -= sunt op de atribuire compusa
	

	//operator +=
	PowerBank& operator+=(int valoare)
	{
		if (this->nivelBaterie + valoare >= 100)
		{
			this->nivelBaterie = 100;
		}
		else
		{
			this->nivelBaterie = this->nivelBaterie + valoare;
		}
		return *this;
	}
	//operator -=
	PowerBank& operator-=(int valoare)
	{
		if (this->nivelBaterie - valoare <= 0)
		{
			this->nivelBaterie = 0;
		}
		else
		{
			this->nivelBaterie = this->nivelBaterie - valoare;
		}
		return *this;
	}
	//operator == face comparatie -> intoarce true sau false
	bool operator==(PowerBank p)
	{
		return(strcmp(this->numeBaterie, p.numeBaterie)==0 && this->nivelBaterie == p.nivelBaterie 
			&& this->pret == p.pret);
	}
	virtual string afisClasaObj()
	{
		return "PowerBank";
	}

};
class PowerBankWireless : public PowerBank
{
	string frecventaWifi;
public:
	PowerBankWireless() : PowerBank()
	{
		this->frecventaWifi = "0.0";
	}
	PowerBankWireless(int idBaterie, const char* numeBaterie, int nivelBaterie, float pret, string frecventaWifi)
		:PowerBank(idBaterie, numeBaterie, nivelBaterie, pret)
	{
		this->frecventaWifi = frecventaWifi;
	}
	PowerBankWireless(const PowerBankWireless& p) : PowerBank(p)
	{
		this->frecventaWifi = p.frecventaWifi;
	}

	//pt destructorul din clasa derivata
	//->intai se distrug atributele din clasa derivata si apoi dupa din clasa de baza
	~PowerBankWireless()
	{
		//nu avem nimic alocat dinamic
	}
	PowerBankWireless& operator=(const PowerBankWireless& p)
	{
		if (this != &p)
		{
			PowerBank :: operator =(p);
			this->frecventaWifi = p.frecventaWifi;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const PowerBankWireless& p)
	{
		out << (PowerBank&)p;
		out << "Frecventa: " << p.frecventaWifi << "gHz" << endl;
		return out;
	}

	 string afisClasaObj()
	{
		return "PowerBankWireless cu o frecventa ridicata!";
	}
};

template<typename tEx>
void afisare(tEx obj)
{
	cout << obj << endl;
}

void main()
{
	PowerBank p;
	cout << p.getNivelBaterie() << endl;
	cout << endl;

	p.setNivelBaterie(70);
	p.setNivelBaterie(370);
	p.setNivelBaterie(-21);
	cout << p.getNivelBaterie() << endl;


	cout << endl << endl;
	PowerBank p1(32, "Xiaomi", 87, 200);
	cout << p1.getNivelBaterie() << endl;

	PowerBank p2(107, "Samsung", 54, 150);
	cout << p2.getNivelBaterie() << endl;

	PowerBank p3(p1);//constr copiere
	cout << p3 << endl;

	p3 = p2;
	cout << p3 << endl;
	cout << endl << endl;

	//testare operatori

	p3 += 11;
	cout << p3 << endl;
	cout << endl << endl;
	p3 -= 23;
	cout << p3 << endl;

	//operator == testare
	PowerBank p4 = p3;
	cout << (p3 == p3) << endl;
	cout << (p2 == p3) << endl;
	cout << (p1 == p3) << endl;
	cout << (p4 == p3) << endl;
	cout << endl << endl;

	PowerBankWireless pw;
	cout << pw << endl;

	PowerBankWireless pw1(40, "Apple", 78,500, "2.1");
	cout << pw1 << endl;

	PowerBankWireless pw2 = pw;
	cout << pw1 << endl;

	pw2 = pw1;
	cout << pw2 << endl;

	//demostrare early binding -> ce se intampla  la momentul compilarii -> stie ce sa apelezee inaimte de a rula codul
	//exemplu creare de obiecte pw1, pw2 sau p1,p2,p;

	//demonstrare late binding ->  creare functie virtuala -> nu stie ce sa apeleze exact->stie doar la momentul rularii
	//->se pune in evidenta doar cand e vorba de mostenire
	PowerBank* ppb = new PowerBank(p1);//apelare constr copiere
	PowerBank* ppb1 = new PowerBankWireless(pw1);//apelare constr copiere

	cout << ppb->afisClasaObj() << endl;
	cout << ppb1->afisClasaObj() << endl;

	cout << endl << endl;
	afisare(222);
	cout << endl;
	afisare("POO");
	cout << endl;
	afisare(p1);
	cout << endl;
	afisare(pw1);
}