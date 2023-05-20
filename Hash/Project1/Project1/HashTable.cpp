#include "HashTable.h"

Student* HashTable::newStudent(unsigned int indeks, string ime, Ispit* ispiti)
{
	Student* tmp = new Student;
	tmp->indeks = indeks;
	tmp->ime = ime;
	tmp->prijavljeni = ispiti;
	return tmp;
}

Ispit* HashTable::newIspit(Ispit* prvi, string naziv)
{
	Ispit* tmp = new Ispit;
	tmp->ispit = naziv;
	tmp->next = nullptr;
	Ispit* curr = prvi;
	if (curr == nullptr) return  tmp;
	while (curr->next != nullptr)
		curr = curr->next;
	curr->next = tmp;
	return prvi;
}

int HashTable::getBaseAddr(unsigned int indeks)
{
	int numbits = this->p;
	int position = 0;
	int mask = 1;
	for (int i = 0; i < numbits; i++)
	{
		if (indeks & mask)
		{
			position += mask;
		}
		mask <<= 1;
	}
	return position;
}

Student* HashTable::findKey(unsigned int indeks)
{
	int i = 0;
	int j;
	int base = getBaseAddr(indeks);
	do
	{
		j = addr->getAddress(indeks,base, i, size);
		for (int k = 0; k < bucketSize; k++)
		{
			if (table[j][k] == nullptr)
				return nullptr;
			else if (table[j][k]->indeks == indeks)
				return table[j][k];
		}
		i += 1;

	} while (this->table[j][0] != nullptr || i < this->size);
	return nullptr;
}

bool HashTable::insertKey(Student* stud,unsigned int indeks)
{
	int i = 0;
	int j;
	int base = getBaseAddr(indeks);
	do
	{
		j = addr->getAddress(indeks, base, i, size);
		/*if (table[j] == nullptr)
		{
			table[j] = stud;
			cout << j << endl;
			return true;
		}
		else if (table[j] == stud)
			return false;*/
		for (int k = 0; k < bucketSize; k++)
		{
			if (table[j][k] == nullptr)
			{
				table[j][k] = stud;
				return true;
			}
			else if (table[j][k]->indeks == stud->indeks) return false;
		}
		i += 1;

	} while (i < size);
	return false;
}

Ispit* HashTable::deleteAllIspit(Student* stud)//vraca nullptr kad sve obrise
{
	if (stud == nullptr) return nullptr;
	Ispit* curr = stud->prijavljeni;
	Ispit* prev = nullptr;
	while (curr != nullptr)
	{
		prev = curr;
		curr = curr->next;
		delete prev;
	}
	//if(prev!=nullptr) delete prev;

	return nullptr;
}

void HashTable::clearMatrix()//brise sve kljuceve ali ostavlja matricu
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < bucketSize; j++)
		{
			if (table[i][j] != nullptr)
			{
				table[i][j]->prijavljeni = deleteAllIspit(table[i][j]);
				delete table[i][j];
				table[i][j] = nullptr;
			}
		}
	}
}

void HashTable::clear()//brise celu matricu
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < bucketSize; j++)
		{
			if (table[i][j] != nullptr)
			{
				table[i][j]->prijavljeni = deleteAllIspit(table[i][j]);
				delete table[i][j];
				table[i][j] = nullptr;
			}
			
		}
		delete table[i];
	}
	delete table;
	table = nullptr;
}

int HashTable::keyCount() const
{
	int brojac = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < bucketSize; j++)
			if (table[i][j] != nullptr && table[i][j]->deleted == false)
				brojac++;
	}
	return brojac;
}

bool HashTable::deleteKey(unsigned int indeks)
{
	Student* tmp = this->findKey(indeks);
	if (tmp == nullptr) return false;
	tmp->deleted = true;
	tmp->indeks = 0;
	tmp->prijavljeni = deleteAllIspit(tmp);
	return true;
}

void HashTable::addIspit(Student* stud,string strIsp)
{
	stud->prijavljeni = newIspit(stud->prijavljeni, strIsp);
}


void HashTable::readFromFile(int len, string fileName)
{
	string duzina = to_string(len);
	unsigned int indeks;
	int brojac;
	bool proba = false;
	fileName = fileName + duzina+".csv";
	string line, ime, predmeti, word;
	ifstream inFile;
	Student* curr=nullptr;
	Ispit* ptrIsp = nullptr;
	inFile.open(fileName);
	getline(inFile, line);
	while (getline(inFile, line, ','))//inFile
	{
		ptrIsp = nullptr;
		//getline(inFile, line, ',');
		indeks = stoi(line);
		getline(inFile, line, ',');
		ime = line;
		getline(inFile, line, '\n');
		stringstream s(line);
		while (s >> word)
		{
			ptrIsp = newIspit(ptrIsp, word);
		}
		curr = newStudent(indeks, ime, ptrIsp);
		proba = insertKey(curr, indeks);
	}
	inFile.close();
}




ostream& operator<<(ostream& it, const HashTable& hash)
{
	Ispit* curr = nullptr;
	for (int i = 0; i < hash.size; i++)
	{
		cout << i << ". ";
		for (int j = 0; j < hash.bucketSize; j++)
		{
			if (hash.table[i][j] == nullptr)
			{
				cout << "EMPTY | ";
				continue;
			}
			if (hash.table[i][j]->deleted)
			{
				cout << "DELETED | ";
				continue;
			}
			cout << hash.table[i][j]->indeks << " " << hash.table[i][j]->ime;
			curr = hash.table[i][j]->prijavljeni;
			while (curr != nullptr)
			{
				cout << " " << curr->ispit;
				curr = curr->next;
			}
			cout << " | ";
		}
		cout << endl;
	}
	return it;
}
