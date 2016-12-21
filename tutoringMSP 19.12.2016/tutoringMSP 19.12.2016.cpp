#include<iostream>
using namespace std;
class Student
{
private:
	const int id;
	char nume[20];
	int nrNote;
	int* note;

public:
	Student() :id(0)
	{
		strcpy(this->nume, "");
		this->nrNote = 0;
		this->note = NULL;
	}
	void afisare()
	{
		cout << "Studentul " << this->nume<<endl;
		cout << "Numar note " << this->nrNote << endl;
		if (this->note!=NULL)
		for (int i = 0; i < this->nrNote; i++)
			cout << "Nota " << i + 1 << " este " << this->note[i] << endl;
		else cout << "Nu exista note de afisat!"<<endl;
	}
	Student(int id, char* nume, int nrNote, int* note) :id(id)
	{
		
		strcpy(this->nume, nume);
		this->nrNote = nrNote;
		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++)
			this->note[i] = note[i];
	}
	
	~Student()
	{
		//cout << "Apel destructor";
		delete[] this->note;
	}
	int operator[](int index){
		if ((index >= 0) && (index < this->nrNote))
			return this->note[index];
		else
			throw exception("Index invalid!");
	}
	Student(const Student& s):id(s.id){
		strcpy(this->nume, s.nume);
		this->nrNote = s.nrNote;
		this->note = new int[s.nrNote];
		for (int i = 0; i < this->nrNote; i++)
			this->note[i] = s.note[i];
	}
	void operator=(Student& s)
	{
		strcpy(this->nume, s.nume);
		this->nrNote = s.nrNote;
		delete[] this->note;
		this->note = new int[s.nrNote];
		for (int i = 0; i < this->nrNote; i++)
			this->note[i] = s.note[i];
	}
	Student operator+(int nota)
	{
		Student s = *this;
		delete[] s.note;
		s.note = new int[this->nrNote + 1];
		for (int i = 0; i < this->nrNote; i++)
			s.note[i] = this->note[i];
		s.note[this->nrNote] = nota;
		s.nrNote = this->nrNote + 1;

		return s;
	}

	operator float()
	{
		float medie=0;
		for (int i = 0; i < this->nrNote; i++)
			medie = medie + this->note[i];
		return medie / this->nrNote;
	}
};
void main()
{
	Student s1;
	s1.afisare();
	int vector[] = { 10, 8 };
	Student s2(12,"Popescu",2,vector);
	s2.afisare();

	cout <<endl<< s2[1]<<endl;

	Student s3 = s2;
	s3.afisare();
	//s1 = s2;

	s2 = s2 + 2;
	s2.afisare();
	cout<<endl<<(float)s2;
}