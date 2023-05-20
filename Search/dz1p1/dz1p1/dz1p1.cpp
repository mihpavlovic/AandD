#include <iostream>
#include <fstream>
#include<string>
#include <queue>
using namespace std;

struct Node
{
	string key;
	string trans;
	Node* parent;
	Node* left;
	Node* right;
};

Node* newNode()
{
	Node* next = new Node;
	next->left = nullptr;
	next->right = nullptr;
	next->parent = nullptr;
	return next;
}

Node* searchBST(Node* root, string need)//vraca pokazivac na cvor ako ga nadje, ako ne vraca nullptr
{
	Node* curr = root;
	while (curr != nullptr && curr->key != need)
	{
		if (curr->key < need)
			curr = curr->right;
		else curr = curr->left;
	}
	return curr;
}

Node* searchBSTparent(Node* root, string need)//vraca pokazivac na oca cvora gde je ili bi trebalo da bude cvor
{
	Node* curr = root;
	Node* parent = nullptr;
	while (curr != nullptr && curr->key != need)
	{
		if (curr->key < need)
		{
			parent = curr;
			curr = curr->right;
		}
		else
		{
			parent = curr;
			curr = curr->left;
		}
	}
	return parent;
}

Node* minimum(Node* root)//vraca najmanji element iz podstabla
{
	Node* curr = root;
	//ako prosledi prazno stablo
	if (curr == nullptr)
		return nullptr;

	while (curr->left != nullptr)
		curr = curr->left;
	return curr;
}

Node* maximum(Node* root)//vraca najveci element iz podstabla
{
	Node* curr = root;
	//ako prosledi prazno stablo
	if (curr == nullptr)
		return nullptr;

	while (curr->right != nullptr)
		curr = curr->right;
	return curr;
}

Node* findSuccessor(Node* root, Node* prev)//vraca inorder sledbenika od poslatog cvora
{
	//ako ne prosledi prev vrati nullptr
	if (prev == nullptr)
		return nullptr;

	Node* curr = prev;
	Node* parent = prev->parent;
	if (curr->right == nullptr)//ako nema desnog potomka penji se gore dok ne dodjes do prvog levog sina
	{
		while (parent != nullptr && parent->right == curr)
		{
			curr = parent;
			parent = parent->parent;
		}
		//if (parent == nullptr) return nullptr;//trazio sam sledbenika od poslednjeg cvora u stablu te on nema sledbenika
	}
	else return minimum(curr->right);//samo nadji minimum podstabla desnog sina
	
	
	return parent;
}

Node* addNode(Node* root, Node* putIn)//vraca pokazivac na root kad unese cvor, nullptr ako je neuspesno
{
	//treba mi pokazivac na oca kod bst
	//ako ga nema u stablu vec
	
	//ako je stablo prazno
	if (root == nullptr)
		return putIn;

	Node *parent, *succ;
	Node* curr = searchBST(root, putIn->key);
	if (curr == nullptr)//ako nema cvora sa ovim kljucem
	{
		parent = searchBSTparent(root, putIn->key);//nadji roditelja cije dete treba da bude cvor koji se ubacuje
		if (parent == nullptr)//ako nema oca od cvora ne moze da se ubaci
			return nullptr;
		if (parent->key < putIn->key)
		{
			parent->right = putIn;
			putIn->parent = parent;
		}
		else
		{
			parent->left = putIn;
			putIn->parent = parent;
		}
	}
	else//ako ovaj kljuc vec postoji u stablu
	{
		if (curr->right == nullptr)//ako nema desnog sina tu je successor
		{
			putIn->parent = curr;
			curr->right = putIn;
		}
		else
		{
			succ = findSuccessor(root, curr);//ako ima desnog sina sig ima i naslednika i ne moram nullptr da gledam
			succ->left = putIn;
			putIn->parent = succ;
		}

	}
	//if (root->parent != nullptr)//za slucaj da se nesto dodalo iznad korena pa da vrati onda novi koren
		//return root->parent;
	return root;
}

Node* deleteNodeLeaf(Node* root,Node* del)
{
	//promena pokazivaca kod oca
	if (del->parent != nullptr)
	{
		if (del->parent->left == del)
			del->parent->left = nullptr;
		else del->parent->right = nullptr;
	}
	else//nema oca znaci sam koren bio
	{
		delete del;
		return nullptr;
	}
	delete del;
	return root;
}

Node* deleteNode1Kid(Node* root, Node* del)
{
	Node* parent = del->parent;
	if (del->left != nullptr)
	{
		if (parent->left == del)
			parent->left = del->left;
		else
			parent->right = del->left;
		del->left->parent = parent;
		//ako sam brisao root
		if (parent == nullptr)
			root = del->left;
	}
	else
	{
		if (parent->left == del)
			parent->left = del->right;
		else
			parent->right = del->right;
		del->right->parent = parent;
		//ako sam brisao root
		if (parent == nullptr)
			root = del->right;
	}
	delete del;
	return root;

}

Node* deleteNode(Node* root, string need)//vraca root ako nadje cvor i null ako ga ne nadje
{
	Node* tmp;
	Node* del = searchBST(root, need);
	//vraca null ako ne nadje
	if (del == nullptr)
		return del;
	while (del != nullptr)
	{
		//ako je cvor za brisanje list
		if (del->right == nullptr && del->left == nullptr)
			root = deleteNodeLeaf(root, del);
		else if (del->right != nullptr && del->left != nullptr)
		{
			tmp = findSuccessor(root, del);
			del->key = tmp->key;
			del->trans = tmp->trans;
			if (tmp->left != nullptr || tmp->right != nullptr)
				root = deleteNode1Kid(root, tmp);
			else root = deleteNodeLeaf(root, tmp);
		}
		else if (del->right != nullptr || del->left != nullptr)
			root = deleteNode1Kid(root, del);
		del = searchBST(root, need);
	}
	return root;
	
	
}

void inorder(Node* root)//rekurzivna provera
{
	if (root != nullptr)
	{
		inorder(root->left);
		cout << root->key << " " << root->trans << endl;
		inorder(root->right);
	}
}

Node* deleteBST(Node* root)//vraca nullptr kad obrise
{
	queue<Node*> toDelete;//red preko kog brisem
	toDelete.push(root);
	Node* curr;
	while (!toDelete.empty())
	{
		curr = toDelete.front();
		toDelete.pop();
		if (curr->left != nullptr)
			toDelete.push(curr->left);
		if (curr->right != nullptr)
			toDelete.push(curr->right);
	}
	return nullptr;
}

Node* mostTranslated(Node* root)
{
	//level order idem po svim cvorovima i prolazim sve njegove successore i pamtim cvor sa najvise succ
	queue<Node*> Q;
	Q.push(root);
	int currNum;
	int maxNum=1;
	Node* curr = nullptr;
	Node* currSucc = nullptr;
	Node* most = root;
	while (!Q.empty())
	{
		//vadjenje iz reda i stavljanje novih u red
		curr = Q.front();
		Q.pop();
		if (curr->left != nullptr) Q.push(curr->left);
		if (curr->right != nullptr) Q.push(curr->right);

		//analiza sledbenika cvora
		currNum = 1;
		currSucc = findSuccessor(root, curr);
		//if (currSucc == nullptr) continue;//ako dodje do toga da nema sledbenika predji na sledeci u redu
		while (currSucc!= nullptr && curr->key == currSucc->key)
		{
			currNum++;
			currSucc = findSuccessor(root, currSucc);
		}
		//ako sam naisao na novog najvise ponovljenog
		if (maxNum < currNum)
		{
			maxNum = currNum;
			most = curr;
		}

	}
	return most;

}

Node* openFromFile()//vraca pokazivac na root-a
{
	Node* root = nullptr;
	Node* curr = nullptr;
	//ifstream read_file("datoteka.txt");
	string line;
	ifstream inFile;
	inFile.open("datoteka.txt");
	while (inFile)
	{
		curr = newNode();
		getline(inFile, line);
		curr->key = line;
		getline(inFile, line);
		curr->trans = line;
		root = addNode(root, curr);

	}
	inFile.close();
	return root;
}

//KORISCEN KOD SA SAJTA ASP2 IZ DOKUMENTA 02_BinTree_src ZA FUNKCIJU printBST
void printBST(Node* root) {
	int treeHeight = 7;
	if (!root)  return;
	else {
		queue<Node*> q;//Queue* q = createQueue((int)pow(2, treeHeight));
		int i, line_len = 62;
		int first_skip = line_len, in_between_skip;

		//if (!q)   return;
		q.push(root);//insertIntoQueue(q, tree->root);
		for (i = 0; i <= treeHeight; i++) {
			int j = 1 << i, k, l;
			in_between_skip = first_skip;
			first_skip = (first_skip - 2) / 2;
			for (k = 0; k < first_skip; k++) putchar(' ');
			for (k = 0; k < j; k++) {
				Node* btn = q.front();//BinTreeNode* btn = (BinTreeNode*)removeFromQueue(q);
				q.pop();
				if (btn) {
					q.push(btn->left);//insertIntoQueue(q, btn->left);
					q.push(btn->right);//insertIntoQueue(q, btn->right);
				}
				else {
					q.push(nullptr);//insertIntoQueue(q, 0);
					q.push(nullptr);//insertIntoQueue(q, 0);
				}
				if (btn)  cout << btn->key <<" " << btn->trans;//printf("%2d", btn->key);
				else       cout << "  ";//printf("  ");
				for (l = 0; l < in_between_skip; l++) cout << " ";//putchar(' ');
			}
			cout << endl;//putchar('\n');
			cout << endl;//putchar('\n');
		}
		//eraseQueue(q);
	}
}

void mainMenu()
{
	Node* root = nullptr;
	bool kraj = false;
	int operacija;
	Node* tmp, * tmp1, * tmp2, * novi;
	cout << "Izaberite neku od sledecih operacija i unesite njen broj." << endl;
	cout << "1 - Formiraj stablo na osnovu skupa reci unetih sa standardnog ulaza" << endl;
	cout << "2 - Formiraj stablo na osnovu skupa reci iz datoteke" << endl;
	cout << "3 - Pronadji prevod zeljene reci" << endl;
	cout << "4 - Ispisi celo stablo" << endl;
	cout << "5 - Obrisi celo stablo" << endl;
	cout << "6 - Pronadji rec sa najvise prevoda" << endl;
	cout << "7 - Dodaj rec sa prevodom" << endl;
	cout << "8 - Obrisi rec i sve njene prevode" << endl;
	cout << "9 - Zavrsi sa programom" << endl;
	string input1, input2;
	
	while (true)
	{
		cout << "Operacija: ";
		cin >> operacija;
		switch (operacija)
		{

		case 1:
			cout << "Unesi skup reci, rec pa prevod redom, da bi zavrsio unesi 'kraj kraj':" << endl;
			while (true)
			{
				cout << "rec:";
				cin >> input1;
				if (input1 == "kraj")//zavrsi ciklus kad upise "kraj"
					break;
				cout << "prevod:";
				cin >> input2;
				novi = newNode();
				novi->key = input1;
				novi->trans = input2;
				root = addNode(root, novi);
			}
			break;

		case 2:
			root = openFromFile();
			if (root == nullptr) cout << "Stablo nije dodato." << endl;
			else cout << "Stablo je uspesno dodato" << endl;
			break;

		case 3:
			cout << "Unesite rec ciji prevod zelite da nadjete" << endl;
			cin >> input1;
			tmp = searchBST(root, input1);
			if (tmp == nullptr)
				cout << "Rec nije pronadjena u recniku." << endl;
			else cout << "Prevod reci " << tmp->key << " je " << tmp->trans << endl;
			break;

		case 4:
			if (root != nullptr)
				printBST(root);
			else cout << "Nije unet nijedan element te stablo ne moze da se ispise." << endl;
			break;

		case 5:
			root = deleteBST(root);
			if (root == nullptr)
				cout << "Stablo je uspesno obrisano." << endl;
			else cout << "Stablo nije uspesno obrisano." << endl;
			break;

		case 6:
			tmp = mostTranslated(root);
			if (tmp != nullptr) cout << "Rec sa najvise prevoda je " << tmp->key << endl;
			else cout << "Desila se greska" << endl;
			break;

		case 7:
			cout << "Upisi rec koju zelis da dodas:";
			cin >> input1;
			cout << "Upisi njen prevod:";
			cin >> input2;
			tmp1 = newNode();
			tmp1->key = input1;
			tmp1->trans = input2;
			tmp2 = addNode(root, tmp1);
			if (tmp2 == nullptr) cout << "Neuspesno dodavanje cvora." << endl;
			else root = tmp2;
			break;

		case 8:
			cout << "Unesi rec koju zelis da obrises:";
			cin >> input1;
			tmp1 = deleteNode(root, input1);
			if (tmp1 == nullptr) cout << "Nema takve reci u stablu." << endl;
			else root = tmp1;
			break;

		case 9:
			kraj = true;
			break;	
		}
		if (kraj) break;
	}
	//inorder(root);
}

int main()
{
	mainMenu();
	return 0;
}