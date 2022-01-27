//Fisier header BinaryTree.h->Contine clasa BinaryTree, ce mosteneste interfata Container, implementata pentru prima data in cadrul operatiilor cu stive, respectiv cozi.
#pragma once
#include "QueueArray.h" //include clasa abstracta Container
#include "stdexcept" //utilizata pentru runtime_error
#include<string>
#include "DoubleLinkedList.h" //foloseste lista dublu inlantuita pentru a converti un arbore binar intr-o structura de acest tip
//Clasa generica Binary Tree, contine implementarea cat si cele mai comune operatii cu arbori binari
template <class T>
class BinaryTree:public virtual Container
{

protected:
	T data;
	//Subarborele stang
	BinaryTree<T>* left;
	//Subarborele drept
	BinaryTree<T>* right;

public:

	//Constructor inline implicit, initializeaza instanta curenta a clasei cu un arbore vid
	BinaryTree() :left(nullptr), right(nullptr) { count = 0; }

	//Constructor inline de initializare:initializeaza radacina arborelui cu nodul ce contine valoarea dt
	BinaryTree(T const& dt):data(dt),left(nullptr),right(nullptr)
	{
		//Variabila membru a clasei Container ce va retine numarul de noduri
		count++;
	}

	//Constructor de initializare
	BinaryTree(T const& dt, BinaryTree<T>*l,BinaryTree<T>*r)
	{
		this->left = l;
		this->right = r;
		this->data = dt;
		this->count = 1+(l!=nullptr?l->count:0) + (r!=nullptr?r->count:0);
	}

	//Constructor inline de copiere, permite copierea unui arbore in instanta curenta
	BinaryTree(BinaryTree<T> const& bin){

		if (bin.isEmpty())
			BinaryTree();
		else {
			count = bin.count;
			left = bin.left ? new BinaryTree<T>(bin.left) : nullptr;
			right = bin.right ? new BinaryTree<T>(bin.right) : nullptr;
			data = bin.data;
		}
	}

	//Metode:

	//Dezaloca memoria utilizata pentru reprezentarea unui arbore prin instanta curenta
	void Destroy();

	//Destructorul, apeleaza metoda destroy pentru a elibera memoria ocupata de arborele curent
	~BinaryTree() { Destroy(); }

	//Accesor utilizat pentru obtinerea valorii stocate intr-un nod al arborelui
	T getData();

	//Obtine subarborele stang
	BinaryTree* getLeft() const;

	//Obtine subarborele drept
	BinaryTree* getRight() const;

	//Seteaza subarborele stang
	void setLeft(BinaryTree<T>* l);

	//Seteaza subarborele drept
	void setRight(BinaryTree<T>* r);

	//Obtine numarul de noduri din arbore
	unsigned int getCount() const override;

	//Verifica daca arborele este sau nu vid (gol)
	bool isEmpty() const override;

	//Afiseaza nodurile arborelui in conformitate cu parcurgerea in preordine (RSD) a acestuia
	void preOrd(void (*disp)(T&));

	//Afiseaza nodurile arborelui in conformitate cu parcurgerea in inordine (SRD) a acestuia
	void inOrd(void (*disp)(T&));

	//Afiseaza nodurile arborelui in conformitate cu parcurgerea in postordine (SDR) a acestuia
	void postOrd(void (*disp)(T&));

	//Afiseaza nodurile arborelui conform parcurgerii in latime a acestuia
	void breadthFirstTraversal(void (*disp)(T&));

	//Compara 2 arbori binari. Returneaza 0 in situatia in care arborii sunt echivalenti, 1, daca primul arbore este mai mare, respectiv -1, in situatia in care cel de-al doilea arbore este mai mare.
	int compareTo(BinaryTree<T>& bt) { return compareBinaryTree(*this, bt); }

	//Construieste un arbore binar echilibrat pornind de la o configuratie a numarului de noduri
	void buildBalanced(unsigned int nodes);

	//Afiseaza arborele binar sub forma parantezata (Key(Left_Tree, Right_Tree)), unde Left_Tree si Right_Tree reprezinta afisarile corespunzatoare ale arborelui stang si drept
	string displayWithParantheses();

	//Obtine numarul de noduri frunza ale arborelui curent
	unsigned int getNumberOfLeaves();

	//Contorizeaza numarul de noduri ale arborelui
	unsigned int getNumberOfNodes();

	//Determina inaltimea arborelui binar
	unsigned int getHeight();

	//Determina latimea unui nivel dintr-un arbore binar (latimea este data de numarul nodurilor de pe acel nivel).
	unsigned int getWidthForLevel(unsigned int level);

	//Determina latimea maxima a arborelui (latimea maxima este data de maximul dintre toate latimile arborelui, sau de numarul maxim de elemente de pe un anumit nivel).
	unsigned int getMaxWidth();

	//Transforma un arbore binar intr-o lista dublu inlantuitaîn in care nodurile sunt puse in ordinea data de traversarea in inordine (SRD) a arborelui.
	DoubleLinkedList<T>toDoubleLinkedList();

	//Transforma un arbore binar intr-un array in care nodurile sunt puse in ordinea data de traversarea in inordine (SRD) a arborelui
	T* inOrdtoArray();

	//Transforma un arbore binar intr-un array in care nodurile sunt puse in ordinea data de traversarea in preordine (RSD) a arborelui
	T* preOrdToArray();

	//Compara 2 arbori binari. Returneaza 0 in situatia in care arborii sunt echivalenti, 1, daca primul arbore este mai mare, respectiv -1, in situatia in care cel de-al doilea arbore este mai mare.
	friend int compareBinaryTree(BinaryTree<T>& bt1, BinaryTree<T>& bt2)
	{
		if(bt1.isEmpty())
		{
			if (bt2.isEmpty())
				return 0; //egale vide
			return -1; //arborele bt2 mai mare
		}

		if (bt2.isEmpty())
			return 1;
			
		if (bt1.data < bt2.data)
			return -1;
				
		if (bt1.data > bt2.data)
			return 1;

		const int res = compareBinaryTree(bt1->left, bt2->left);

		if (res == 0)	
			return compareBinaryTree(bt1.right, bt2->right);

		return res;

	}

//Metoda privata face referire la metoda isFull(), ce a fost definita in clasa de baza Container in mod special pentru structurile de date statice (stive,cozi), ce aveau ca suport de stocare un array. Intrucat arborele binar pe care aceasta clasa il figureaza detine o implementare dinamica, metoda nu ar putea niciodata sa returneze true. Implementarea acesteia este obligatorie in aceasta clasa, datorita ierarhiei in cauza, rolul acesteia nefiind unul important in vederea implementarii structurii de arbori binari.
private:
	bool isFull() const override { return false; }

	//Realizeaza parcurgerea inordine (SRD) a arborelui binar si stocheaza rezultatele intr-o coada statica
	string inOrdToString();

	//Realizeaza parcurgerea preordine (RSD) a arborelui binar si stocheaza rezultatele intr-o coada statica
	string preOrdToString();

};

//Definitii metode clasa BinaryTree
//Dezaloca memoria utilizata pentru reprezentarea unui arbore in memorie prin instanta curenta
template <class T>
void BinaryTree<T>::Destroy()
{
	if (left != nullptr) {
		left->Destroy();
		delete left;
	}
	if(right!=nullptr)
	{
		right->Destroy();
		delete right;
	}
	//Reinitializare
	left = right = nullptr;
	count = 0;
	
}

//Accesor utilizat pentru obtinerea valorii stocate intr-un nod al arborelui
template <class T>
T BinaryTree<T>::getData() 
{
	return data;
}

//Obtine subarborele stang
template <class T>
BinaryTree<T>* BinaryTree<T>::getLeft() const
{
	return left;
}

//Obtine subarborele drept
template <class T>
BinaryTree<T>* BinaryTree<T>::getRight() const
{
	return right;
}

//Seteaza subarborele stang
template <class T>
void BinaryTree<T>::setLeft(BinaryTree<T>* l)
{
	if (isEmpty())
		throw std::runtime_error("EROARE!\nArborele este vid!\n");
	if (left != nullptr && left != l)
		left->Destroy();
	left = l;
	count = 1+(left ? left->getCount() : 0) + (right ? right->getCount() : 0);

}

//Seteaza subarborele drept
template <class T>
void BinaryTree<T>::setRight(BinaryTree<T>* r)
{
	if (isEmpty())
		throw std::runtime_error("EROARE!\nArborele este vid!\n");
	if (left != nullptr && left != r)
		left->Destroy();
	left = r;
	count = 1 + (left ? left->getCount() : 0) + (right ? right->getCount() : 0);

}

//Obtine numarul de noduri al arborelui curent
template <class T>
unsigned BinaryTree<T>::getCount() const
{
	return count;
}

//Verifica daca arborele este sau nu vid
template <class T>
bool BinaryTree<T>::isEmpty() const
{
	return count == 0;
}

//Functie utilitara, ce va fi utilizata pentru afisarea nodurilor arborelui binar, in cazul celor 3 parcurgeri
template<class T>
void disp(T& val)
{
	std::cout << val << "\t";
}

//Afiseaza nodurile arborelui in conformitate cu parcurgerea in preordine (RSD) a acestuia
template <class T>
void BinaryTree<T>::preOrd(void (* disp)(T&))
{
	disp(data);
	if (left != nullptr)
		left->preOrd(disp);//apel recursiv
	if (right != nullptr)
		right->preOrd(disp);//apel recursiv
}

//Afiseaza nodurile arborelui in conformitate cu parcurgerea in inordine (SRD) a acestuia
template <class T>
void BinaryTree<T>::inOrd(void (* disp)(T&))
{
	if (left != nullptr)
		left->inOrd(disp);//apel recursiv
	disp(data);
	if (right != nullptr)
		right->inOrd(disp);//apel recursiv
}

//Afiseaza nodurile arborelui in conformitate cu parcurgerea in postordine (SDR) a acestuia
template <class T>
void BinaryTree<T>::postOrd(void (* disp)(T&))
{
	if (left != nullptr)
		left->postOrd(disp);//apel recursiv
	if (right != nullptr)
		right->postOrd(disp);//apel recursiv
	disp(data);
}

//Afiseaza nodurile arborelui conform parcurgerii in latime a acestuia
template <class T>
void BinaryTree<T>::breadthFirstTraversal(void (* disp)(T&))
{
	QueueArray<BinaryTree<T>*>q;

	if (isEmpty())
		return;//arborele este vid
	q.enQueue(this);

	while(!q.isEmpty())
	{
		BinaryTree<T>* bt = q.getHead();
		q.deQueue();
		if(!bt->isEmpty())
		{
			disp(bt->getData());
			q.enQueue(bt->left);
			q.enQueue(bt->right);
		}
	}
}

//Construieste un arbore binar echilibrat pornind de la o configuratie a numarului de noduri
template <class T>
void BinaryTree<T>::buildBalanced(unsigned int nodes)
{
	unsigned int ln, rn;

	//Valoarea ce va urma a fi stocata
	T inf;
	if (nodes == 0)
		this->Destroy();

	count = nodes;
	std::cout << "Valoarea din nod: "; std::cin >> inf;
	data = inf;
	//Left nodes, right nodes
	 ln = (nodes - 1) / 2;
	 rn = nodes - ln - 1;

	if(ln>0)
	{
		this->left = new BinaryTree<T>;
		this->left->buildBalanced(ln);
	}

	if(rn>0)
	{
		this->right = new BinaryTree<T>;
		this->right->buildBalanced(rn);
	}
}

//Obtine numarul de noduri frunza ale arborelui curent
template <class T>
unsigned int BinaryTree<T>::getNumberOfLeaves()
{
	//Arbore sau subarbore vid
	if (this == nullptr)
		return 0;

	//Radacina
	if (this->left == nullptr && this->right == nullptr)
		return 1;

	//Subarborii (apel recursiv)
	return this->left->getNumberOfLeaves() + this->right->getNumberOfLeaves();
}

//Contorizeaza numarul de noduri ale arborelui
template <class T>
unsigned int BinaryTree<T>::getNumberOfNodes()
{
	//Variabila in care vom stoca numarul nodurilor
	unsigned int nodes = 0;

	if (this == nullptr)
		return 0;

	//Apel recursiv:determina numarul de noduri pentru subarborele stang si drept si la final, returnam numarul de noduri ca o suma de noduri pentru fiecare subarbore in parte
	return 1 + this->left->getNumberOfNodes() + this->right->getNumberOfNodes();
}

//Determina inaltimea arborelui binar. Aceasta este data de radacina (inaltime 1), la care se adauga maximul inaltimii dintre subarborele stang si cel drept
template <class T>
unsigned BinaryTree<T>::getHeight()
{
	//Daca arborele este vid, inaltimea este 0
	if (this == nullptr)
		return 0;
	//Inaltimea arborelui este data de radacina (1)+maximul dintre subarborele stang si cel drept
	return 1 + max(left->getHeight(), right->getHeight());
}

//Afiseaza arborele binar sub forma parantezata (Key(Left_Tree, Right_Tree)), unde Left_Tree si Right_Tree reprezinta afisarile corespunzatoare ale arborelui stang si drept
template <class T>
string BinaryTree<T>::displayWithParantheses()
{
	//Arbore vid, se va returna string-ul vid
	if (this == nullptr)
		return "";
	//Deschidem paranteza
	string output = "(";

	//Inseram informatia stocata in nodul arborelui
	output += to_string(this->data);

	//2 apeluri recursive, pentru subarborele stang si cel drept
	output += left->displayWithParantheses();
	output += right->displayWithParantheses();

	//Inchidem paranteza
	output += ")";

	//Returnam valoarea ce va urma a fi afisata.
	return output;
}

//Determina latimea unui nivel dintr-un arbore binar (latimea este data de numarul nodurilor de pe acel nivel).
template <class T>
unsigned BinaryTree<T>::getWidthForLevel(unsigned int level)
{
	//Daca se introduce o valoare invalida (nula)
	if (level == 0)
		throw runtime_error("EROARE!\n Parametrul introdus nu descrie un nivel valid al arborelui!\n");

	//Arbore vid
	if (this == nullptr)
		return 0;

	//Nivelul 1, ce contine doar radacina
	if (level == 1)
		return 1;

	//Apelul recursiv
	return left->getWidthForLevel(level - 1) + right->getWidthForLevel(level - 1);
}

//Determina latimea maxima a arborelui (latimea maxima este data de maximul dintre toate latimile arborelui, sau de numarul maxim de elemente de pe un anumit nivel).
template <class T>
unsigned BinaryTree<T>::getMaxWidth()
{
	unsigned int maximum = 0;
	//Parcurgem fiecare nivel al arborelui si apelam metoda getWidthForLevel pentru fiecare din aceste nivele, pentru a gasi latimea maxima a arborelui
	for (int i = 1; i <= this->getHeight(); i++)

		if (this->getWidthForLevel(i) > maximum)
			maximum = this->getWidthForLevel(i);

	return maximum;
}



//Realizeaza parcurgerea inordine (SRD) a arborelui binar si stocheaza rezultatele intr-un string
template <class T>
string BinaryTree<T>::inOrdToString()
{
	string result;
	if (left != nullptr)
		result += left->inOrdToString() + " ";//apel recursiv
	result += to_string(data) + " ";
	if (right != nullptr)
		result+=right->inOrdToString()+" ";//apel recursiv

	return result;
}

//Realizeaza parcurgerea inordine (RSD) a arborelui binar si stocheaza rezultatele intr-un string
template <class T>
string BinaryTree<T>::preOrdToString()
{
	string result;
	result += to_string(data);
	if (left != nullptr)
		result += left->preOrdToString() + " "; //apel recursiv
	if (right != nullptr)
		result += right->preOrdToString() + " "; //apel recursiv
	return result;
}

//Transforma un arbore binar intr-o lista dublu inlantuitaîn in care nodurile sunt puse in ordinea data de traversarea in inordine a arborelui.
//Metoda apeleaza procedura inOrdToString, care transforma valorile obtinute, ca urmare a parcurgerii inordine intr-un sir de caractere
template <class T>
DoubleLinkedList<T> BinaryTree<T>::toDoubleLinkedList()
{
	DoubleLinkedList<T>dl;
	const string str= this->inOrdToString();
	for (const char i : str) {
		if (i != ' ') {
			//Daca template-ul este un intreg, vom face conversia la int
			if (sizeof(T) == 4)
				dl.addLast(i - '0');
			else //altfel, construim lista pe baza de string-uri
				dl.addLast(i);
		}
	}
	return dl;
}

//Transforma un arbore binar intr-un array in care nodurile sunt puse in ordinea data de traversarea in inordine (SRD) a arborelui
template <class T>
T* BinaryTree<T>::inOrdtoArray()
{
	T* res = new T[this->count];
	unsigned int idx = 0;
	const string str = this->inOrdToString();

	for(const char i:str)
	{
		if(i!=' '){
		if (sizeof(T) == 4) {
			*(res + idx) = i - '0';
		}
		else
			*(res + idx) = i;
		idx++;
		}

	}

	return res;
}

//Transforma un arbore binar intr-un array in care nodurile sunt puse in ordinea data de traversarea in preordine (RSD) a arborelui
template <class T>
T* BinaryTree<T>::preOrdToArray()
{
	unsigned int idx = 0;
	T* res = new T[this->count];
	const string str = this->preOrdToString();

	for(const char i:str)
	{
		if (i != ' ') {
			if (sizeof(T) == 4) {
				*(res + idx) = i - '0';
			}
			else
				*(res + idx) = i;
			idx++;
		}

	}
	return res;
}

#pragma endregion












