#include<iostream>
#include<fstream>
using namespace std;
//definirea unei clase
class Student
{protected:
const int id;
	char* nume;
	char prenume[30];
	int nrNote;
	int * note;
	static int nrStudenti;
public:
	virtual int medie(){
		int s = 0;
		for (int i = 0; i < this->nrNote; i++)
			s += this->note[i];
		return s / this->nrNote;
	}
	//virtual void medie()= 0;
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
		cout << "Id: " << this->id << endl;
		if (this->nume != NULL)
			cout << "Nume: " << this->nume << endl;
		else
			cout << "Nu exista nume!" << endl;
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
	Student operator=(const Student& s)
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
		return*this;

	}
	//getteri
	int getId(){
		return this->id;
	}
	char* getNume()
	{
		return this->nume;
	}
	char* getPrenume(){
		return this->prenume;
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
		else
			throw exception("Nume invalid!");
	}
	void setPrenume(char* prenume){
		if (strlen(prenume)>2)
			strcpy(this->prenume, prenume);
		else
			throw exception("Prenume prea scurt!");

	}
	void setNote(int* note, int n){
		if (n > 0)
		{
			this->nrNote = n;
			delete[]this->note;
			this->note = new int[n];
			for (int i = 0; i < n; i++)
				this->note[i] = note[i];
		}
		else
			throw exception("Nu se poate schimba vectorul de note!");

	}
	friend ostream& operator<<(ostream& out, const Student& s);
	friend istream& operator>>(istream& in, Student& s);
	int operator[](int n)
	{
		if ((n >= 0) && (n < this->nrNote))
			return this->note[n];

	}
	friend ifstream& operator>>(ifstream& in, Student& s);
};
int Student::nrStudenti = 0;

istream& operator>>(istream& in, Student& s)
{
	cout << "Nume: ";
	/*delete[] s.getNume();
	char buffer[100];
	in >>buffer;
	s.nume = new char[strlen(buffer) + 1];
	strcpy(s.nume, buffer);*/
	char buffer[100];
	in >> buffer;
	s.setNume(buffer);
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
	for (int i = 0; i < s.nrNote; i++)
		out << "Nota " << i + 1 << " este: " << s.note[i] << endl;
	out << "Numar studenti: " << s.nrStudenti << endl;
	return out;
}

ifstream& operator>>(ifstream& in, Student& s){
	if (in.is_open()){
		char nume[100];
	//	in >> nume;
		in.getline(nume, 100);
		s.setNume(nume);
		char prenume[30];
		in.getline(prenume, 30);
		s.setPrenume(prenume);
		int nrNote;
		in >> nrNote;
		int note [50];
		for (int i = 0; i < nrNote; i++)
			in >> note[i];
		s.setNote(note, nrNote);
	}
	else cout << "Eroare";
	return in;
}
ofstream& operator<<(ofstream& out, Student& s){
	out << s.getId() << endl;
	out << s.getNume() << endl;
	out << s.getPrenume() << endl;
	out << s.getNrNote() << endl;
	for (int i = 0; i < s.getNrNote(); i++)
		out << s.getNote()[i] << endl;
	return out;
}

class Masterand: public Student{
	int serieDiplomaLicenta;
public:
	Masterand(int serie, int id, char* nume, char* prenume, int nrNote, 
		int* note) :Student(id,nume,prenume,nrNote,note){
		this->serieDiplomaLicenta = serie;
	}
	/*void medie{
		cout << "ceva";
	}*/
	//supradefinire
	int medie(){
		int s = 0;
		for (int i = 0; i < this->nrNote; i++)
			s += this->note[i];
		return (s / this->nrNote)+1;
	}

	Masterand(const Masterand& m){
		this->nume = new char[strlen(m.nume) + 1];
		strcpy(this->nume, m.nume);
		strcpy(this->prenume, m.prenume);
		this->nrNote = m.nrNote;
		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++)
			this->note[i] = m.note[i];
		this->serieDiplomaLicenta = m.serieDiplomaLicenta;
	}
	Masterand operator=(const Masterand& m){
		delete[]this->nume;
		this->nume = new char[strlen(m.nume) + 1];
		strcpy(this->nume, m.nume);
		strcpy(this->prenume, m.prenume);
		this->nrNote = m.nrNote;
		delete[]this->note;
		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++)
			this->note[i] = m.note[i];
		this->serieDiplomaLicenta = m.serieDiplomaLicenta;
		return *this;
	}
};
void main()
{
	Student s1;
	s1.afisare();
	int vector[] = { 8, 9,6 };
	Student s2(12, "Pripas", "Alexandru", 2, vector);
	s2.afisare();
	Student s3(77, "Romaniuc", "Radu");
	s3.afisare();
	Student s4 = s2;
	s4.afisare();
	s1 = s3;
	s1.afisare();
	cout << s2.getNume() << endl;
	for (int i = 0; i < s4.getNrNote(); i++)
		cout << s4.getNote()[i] << " ";
	s2.setNume("Alin");
	s2.afisare();
	//cout << s2;
	//cin >> s1;
	//cout << s1;
	cout << s2[1];
	//un fisier de intrare intrare.txt 
	cout << s1;
	ifstream f;
	f.open("intrare.txt", ios::in);
	f >> s1;
	f.close();
	cout << s1;
	ofstream g;
	g.open("iesireStudent.txt", ios::out | ios::app);
	g << s1;
	g.close();
	Masterand M1(763415, 3, "Andrei", "VAsile", 3, vector);
	Masterand M2(457365, 5, "Andrei", "VAsile", 3, vector);
	Masterand M3(763415, 3, "Andrei", "VAsile", 3, vector);
	M1 = M3 = M2;
	Student s5(12, "Pripas", "Alexandru", 3, vector);

	Student * lista[2];
	lista[0] = new Masterand(457365, 5, "Andrei", "VAsile", 3, vector);
	lista[1] = new Student(12, "Pripas", "Alexandru", 3, vector);
	for (int i = 0; i < 2; i++)
		cout << lista[i]->medie() << endl;
}