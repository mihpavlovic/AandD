#ifndef _HashTable_h_
#define _HashTable_h_
#include"QuadriaticHashing.h"
#include<fstream>
#include<string>
#include<sstream>
struct Ispit
{
	string ispit;
	Ispit* next=nullptr;
};
struct Student
{
	unsigned int indeks;
	string ime;
	Ispit* prijavljeni;
	bool deleted=false;
};
//koristim nullptr kao empty

class HashTable
{
	Student*** table;
	int p;
	int size;
	QuadriaticHashing* addr;
	int bucketSize;
	int getBaseAddr(unsigned int indeks);
	Ispit* deleteAllIspit(Student* stud);
	void clear();
public:
	//konstruktori i operatori dodele
	HashTable(int bits, int coef, int bucket): p(bits), addr(new QuadriaticHashing(coef)), bucketSize(bucket)
	{	
		size = pow(2, p);
		table = new Student ** [size];
		for (int i = 0; i < size; i++)
		{
			table[i] = new Student * [bucket];
			for (int j = 0; j < bucket; j++)//postavljanje svih elem na nullptr
				table[i][j] = nullptr;
		}
	}
	//destruktor
	~HashTable()
	{
		clear();
		delete addr;
	}

	//metode
	//unsigned int getIndeks(Student* stud)const { return indeks; }
	Student* findKey(unsigned int indeks);
	bool insertKey(Student* stud,unsigned int indeks);
	bool deleteKey(unsigned int indeks);
	void clearMatrix();
	
	int keyCount() const;
	int tableSize() const { return size; }//vraca broj ulaza
	double fillRatio() const { return double(keyCount()) / double(tableSize()); }
	void readFromFile(int len,string fileName="students_");
	Student* newStudent(unsigned int indeks, string ime, Ispit* ispiti);
	Ispit* newIspit(Ispit*, string);
	void addIspit(Student*, string);
	//preklopljeni operatori
	friend ostream& operator<<(ostream&,const HashTable&);

	


};
#endif

