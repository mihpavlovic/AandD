#include"HashTable.h"

void mainMenu()
{
	int i, p, c, b, broj;
	unsigned int indeks;
	string ime,prezime, strIsp;
	Ispit* ptrIsp=nullptr;
	Student* stud = nullptr;
	bool kraj = false;
	bool provera;
	cout << "Unesi koliko poslednjih bitova se uzima da kljuc hes tabele,\n koefijent za racunanje indeksa i velicinu baketa redom:";
	cin >> p >> c >> b;
	HashTable hash(p, c, b);
	while (true)
	{
		cout << endl;
		cout << "1 - Unesi studenta sa ispitima preko konzole " << endl;
		cout << "2 - Unesi studente preko datoteke" << endl;
		cout << "3 - Dodaj odredjenom studentu ispit" << endl;
		//cout << "4 - Skini odredjenom studentu ispit" << endl;
		cout << "5 - Pretrazi studenta po indeksu" << endl;
		cout << "6 - Obrisi studenta" << endl;
		cout << "7 - Ispisi hes tabelu" << endl;
		cout << "8 - Obrisi hes tabelu" << endl;
		cout << "9 - Kraj programa" << endl;
		cout << endl;
		cout << "Unesi operaciju:" << endl;
		cin >> i;
		switch (i)
		{
		case 1:
			ptrIsp = nullptr;
			cout << "Unesi broj indeksa:";
			cin >> indeks;
			cout << "Unesi ime i prezime: ";
			cin >> ime >> prezime;
			ime += " ";
			ime += prezime;
			cout << "Unesi ispite, zavrsi sa unosom KRAJ: ";
			cin >> strIsp;
			while (strIsp != "KRAJ")
			{
				ptrIsp = hash.newIspit(ptrIsp, strIsp);
				cout << "Unesi sledeci ispit: ";
				cin >> strIsp;
			}
			stud = hash.newStudent(indeks, ime, ptrIsp);
			if (hash.insertKey(stud, indeks))
				cout << "Student je uspesno dodat." << endl;
			else cout << "Student nije dodat." << endl;
			break;

		case 2:
			cout << "Unesi broj iz imena fajla koji zelis da uneses:";
			cin >> broj;
			hash.readFromFile(broj);
			break;

		case 3:
			cout << "Unesi indeks studenta kojem hoces da dodas ispit:";
			cin >> indeks;
			stud = hash.findKey(indeks);
			if (stud != nullptr)
			{
				cout << "Student je uspesno pronadjen\nUpisi naziv predmeta:";
				cin >> strIsp;
				hash.addIspit(stud, strIsp);
				cout << "Ispit je uspesno dodat" << endl;
			}
			else cout << "Student sa ovim indeksom nije pronadjen te mu s e ne moze dodati ispit." << endl;
			break;

		//case 4:
			//break;

		case 5:
			cout << "Unesi indeks koji zelis da pretrazis:";
			cin >> indeks;
			stud = hash.findKey(indeks);
			if (stud != nullptr)
				cout << "Pronadjen je student i zove se "<<stud->ime << endl;
			else cout << "Student nije pronadjen" << endl;

			break;

		case 6:
			cout << "Unesi indeks studenta kojeg zelis da obrises:";
			cin >> indeks;
			provera = hash.deleteKey(indeks);
			if (provera)
				cout << "Student je uspesno obrisan." << endl;
			else cout << "Student nije uspesno obrisan." << endl;
			break;

		case 7:
			cout << hash;
			break;

		case 8:
			hash.clearMatrix();
			break;

		case 9:
			kraj = true;
			break;
		}
		if (kraj) break;

	}
}
int main()
{
	//HashTable x(8, 2, 3);
	//x.readFromFile(500);
	//cout << x;
	mainMenu();
	
	return 0;
}