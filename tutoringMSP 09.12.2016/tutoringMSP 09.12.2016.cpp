#include<iostream>
using namespace std;
//definirea unei clase
class Student
{
	const int id;
	char* nume;
	char prenume[30];
	int nrNote;
	int * note;
	static int nrStudenti;


public:
	Student() :id(0)
	{
		Student::nrStudenti++;
	//	this->nrStudenti++;
		this->nume = NULL;
		//this->prenume = '\0'; ASA NU
		strcpy(this->prenume, "Anonim");
		this->nrNote = 0;
		this->note = NULL;
	}
	void afisare()
	{
		cout << "Id: " << this->id<<endl;
		if (this->nume != NULL)
			cout << "Nume: " << this->nume << endl;
		else
			cout << "Nu exista nume!"<<endl;
		cout << "Prenume: " << this->prenume << endl;
		if (this->nrNote != 0)
		{
			cout << "Nr note: " << this->nrNote << endl;
			for (int i = 0; i < this->nrNote; i++)
				cout << "Nota " << i + 1 << " este: " << this->note[i] << endl;
		}
		else
			cout << "Nu exista note de afisat! " << endl;
		cout << "Numar sudenti: " << this->nrStudenti << endl;
	}
	Student(int id, char* nume, char* prenume, int nrNote, int* note) :id(id)
	{
		Student::nrStudenti++;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		strcpy(this->prenume, prenume);
		this->nrNote = nrNote;
		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++)
			this->note[i] = note[i];
	}
	Student(int id, char* nume, char* prenume) :id(id)
	{
		Student::nrStudenti++;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		strcpy(this->prenume, prenume);
		this->nrNote = 0;
		this->note = NULL;
	}
	Student(const Student& s) :id(s.id)
	{
		Student::nrStudenti++;
		this->nume = new char[strlen(s.nume) + 1];
		strcpy(this->nume, s.nume);
		strcpy(this->prenume, s.prenume);
		this->nrNote = s.nrNote;
		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++)
			this->note[i] = s.note[i];
	}
	~Student()
	{
		delete[] this->nume;
		delete[] this->note;
	}
	void operator=(const Student& s)
	{
		delete[] this->nume;
		this->nume = new char[strlen(s.nume) + 1];
		strcpy(this->nume, s.nume);
		strcpy(this->prenume, s.prenume);
		this->nrNote = s.nrNote;
		delete[] this->note;
		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++)
			this->note[i] = s.note[i];
		
	}
	//getteri
	char* getNume()
	{
		return this->nume;
	}
	int getNrNote()
	{
		return this->nrNote;
	}
	int* getNote()
	{
		return this->note;
	}
	void setNume(char* nume)
	{
		if (strlen(nume) > 2)
		{
			delete[] this->nume;
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		else throw exception("Nume invalid!");
	}
	friend ostream& operator<<(ostream& out, const Student& s);
	friend istream& operator>>(istream& in, Student& s);
	int operator[](int n)
	{
		if ((n >= 0) && (n < this->nrNote))
			return this->note[n];

	}

};
int Student::nrStudenti = 0;
istream& operator>>(istream& in,  Student& s)
{
	cout << "Nume: ";
	delete[] s.nume;
	char buffer[100];
	in >>buffer;
	s.nume = new char[strlen(buffer) + 1];
	strcpy(s.nume, buffer);
	cout << "Prenume: "; in >> s.prenume;
	cout << "Nr note: "; in >> s.nrNote;
	delete[] s.note;
	s.note = new int[s.nrNote];
	for (int i = 0; i < s.nrNote; i++)
	{
		cout << "Dati nota: "; 
		in >> s.note[i];
	}
	return in;
}
ostream& operator<<(ostream& out, const Student& s)
{
	out << "Id: " << s.id << endl;

	out << "Nume: " << s.nume << endl;
	out << "Prenume: " << s.prenume << endl;
	out << "Numar note: " << s.nrNote << endl;
	out << "	Note " << endl;
	for (int i = 0; i < s.nrNote;i++)
		out << "Nota " <<i+1<<" este: " <<s.note[i] << endl;
	out << "Numar studenti: " << s.nrStudenti << endl;
	return out;
}


void main()
{
	Student s1;
	s1.afisare();
	int vector[] = { 8, 9 };
	Student s2(12,"Pripas","Alexandru",2,vector);
	s2.afisare();
	Student s3(77,"Romaniuc","Radu");
	s3.afisare();
	Student s4 = s2;
	s4.afisare();
	s1 = s3;
	s1.afisare();
	cout<<s2.getNume()<<endl;
	for (int i = 0; i < s4.getNrNote(); i++)
		cout << s4.getNote()[i] << " ";

	s2.setNume("Alin");
	s2.afisare();
	//cout << s2;
	//cin >> s1;
	//cout << s1;
	cout << s2[1];
}