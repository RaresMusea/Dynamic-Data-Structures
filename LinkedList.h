//Fisier LinkedList.h->Contine clasa necesara definirii si implementarii principalelor operatii referitoare la structura de lista simplu inlantuita

#pragma once
#include "Exceptions.h"
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include "Array.h"
using namespace std;

template <class T>
class LinkedList; //Prototipul clasei generice LinkedList

//Clasa generica ListItem, se refera la un element al unei liste inlantuite
template <class T>
class ListItem
{

public:
	T data;
	ListItem* next = nullptr;


public:

	//Constructor inline de initializare, seteaza informatia din nodul curent al listei si adresa de memorie al urmatorului element al acesteia
	ListItem(T const& Data, ListItem<T>* Next) :data(Data), next(Next){}

	//Obtine informatia din nodul curent al listei
	T const& getData() const;

	//Obtine informatia din urmatorul nod al listei
	ListItem* getNext() const;

	//Seteaza informatia din nodul curents
	void setData(T Data);

	//Seteaza adresa de memorie a urmatorului element
	void setNext(ListItem* Next);


	//Clasa LinkedList va avea acces la variabilele membru ale acestei clase
	friend LinkedList<T>;



};

//Definitii metode ListItem:
//Obtine informatia din nodul curent al listei
template <class T>
T const& ListItem<T>::getData() const
{
	return this->data;
}

//Obtine adresa urmatorului nod al listei
template <class T>
ListItem<T>* ListItem<T>::getNext() const
{
	return next;
}

//Seteaza adresa de memorie a urmatorului nod
template <class T>
void ListItem<T>::setNext(ListItem* Next)
{
	this->next = Next;
}

//Seteaza valoarea elementului din nodul curent
template <class T>
void ListItem<T>::setData(T Data)
{
	this->data = Data;
}


//Definitia clasei LinkedList, implementeaza structura de tip Lista inlantuita
template <class T>
class LinkedList
{
	//Retin adresele inceputului, respectiv sfarsitului listei
	ListItem<T>* head;
	ListItem<T>* tail;


public:

	//Constructor inline implicit, seteaza head si tail cu valoarea nullptr
	LinkedList() :head(nullptr), tail(nullptr){}

	//Constructor inline de copere, permite copierea unei liste pasate ca si parametru in obiectul curent
	LinkedList(LinkedList<T> const& list):head(nullptr),tail(nullptr)
	{
		for(auto i=list.head;i!=nullptr;i=i->next)
		{
			addAtTail(i->data);
		}
	}

	//Dealoca memoria ocupata de o lista
	void Destroy();

	//Destructorul,apeleaza metoda Destroy
	~LinkedList() { Destroy(); }

	//Obtine primul element al listei
	ListItem<T>* getHead() const;

	//Obtine elementul de la sfarsitul listei
	ListItem<T>* getTail() const;

	//Verifica daca lista este sau nu populata cu elemente
	bool isEmpty() const;

	//Adauga un nod nou, la inceputul listei
	 void addAtHead(T const& item);

	//Adauga un nod nou, la sfarsitul listei
	void addAtTail(T const& item);

	//Obtine primul element al listei
	T const& getFirst() const;

	//Obtine ultimul element al listei
	T const& getLast() const;

	LinkedList<T>& operator = (LinkedList<T> const& list);

	//Elimina primul element al listei
	void removeFromHead();

	//Elimina ultimul element al listei
	void removeFromTail();

	//Elimina elementul item din lista
	void extract(T const& item);

	//Insereaza in lista un nou element dupa elementul specificat
	void insertAfter(ListItem<T>* arg, T const& item);

	//Insereaza in lista un nou element inaintea elementului specificat
	void insertBefore(ListItem<T>* arg, T const& item);

	//Elimina din lista elementul pozitionat in lista dupa nodul pasat drept parametru
	T& removeAfter(ListItem<T>* arg);

	//Inverseaza o lista simplu inlantuita
	LinkedList<T>& reverse();

	//Separa o lista simplu inlantuita in doua liste inlantuite astfel incat nodurile primei liste sa mearga alternant in cele doua liste.
	LinkedList<T>* split();

	//Elimina elementele duplicate din lista
	void removeDuplicates();

	//Sorteaza lista in ordine crescatoare
	void sortAscending();

	//Adauga valori in lista simplu inlantuita in asa fel incat aceasta sa se pastreze sortata crescator
	void addValue(T val);

	//Interclaseaza doua liste simplu inlantuite
	LinkedList<T> merge(LinkedList<T> el);

	//Cauta valoarea val in lista simplu inlantuita
	bool find(T const& val);

	//Calculeaza intersectia a doua liste simplu inlantuite
	LinkedList<T> intersect(LinkedList<T> l);


	void readWhileSorting();

	friend ostream& operator << (ostream &ostr, LinkedList<T> li)
	{
		if (li.isEmpty()) {
			ostr << "Lista este goala!\n";
			return ostr;
		}

		LinkedList<T>copy = li;
		while(!copy.isEmpty())
		{
			cout << copy.getFirst() << '\t';
			copy.removeFromHead();
		}
		return ostr;
	}
};

//Definitii Metode clasa LinkedList
//Dealoca memoria ocupata de o lista
template <class T>
void LinkedList<T>::Destroy()
{
	while(head)
	{
		const ListItem<T>* aux = head;
		head = head->next;
		delete aux;
	}

	tail = nullptr;
}

//Obtine primul element al listei
template <class T>
ListItem<T>* LinkedList<T>::getHead() const
{
	return head;
}

//Obtine elementul de la sfarsitul listei
template <class T>
ListItem<T>* LinkedList<T>::getTail() const
{
	return tail;
}

//Verifica daca lista este sau nu populata cu elemente
template <class T>
bool LinkedList<T>::isEmpty() const
{
	return (head ==nullptr);
}

//Adauga un nod nou, la inceputul listei
template <class T>
void LinkedList<T>::addAtHead(T const& item)
{
	ListItem<T>* tmp = new ListItem<T>(item, head);
	if (head == nullptr)
		tail=tmp;
	head = tmp;
}

//Adauga un nod nou, la sfarsitul listei
template <class T>
void LinkedList<T>::addAtTail(T const& item)
{
	ListItem<T>*aux= new ListItem<T>(item, nullptr);

	if (head == nullptr)
		head = aux;
	else
		tail->next = aux;
	tail = aux;

}

//Obtine primul element al listei
template <class T>
T const& LinkedList<T>::getFirst() const 
{
	try {
		if (head==nullptr)
			throw ListException();
		return head->data;
	}
	catch(ListException &le)
	{
		le.handle("EROARE!\nLista este goala!");
	}
}

//Obtine ultimul element al listei
template <class T>
T const& LinkedList<T>::getLast() const
{
	try {
		if (tail==nullptr)
			throw ListException();
		return tail->data;
	}
	catch (ListException&le)
	{
		le.handle("EROARE!\nLista este goala!");
	}
}

template <class T>
LinkedList<T>& LinkedList<T>::operator = (LinkedList<T> const& list)
{
	if(&list!=this)
	{
		Destroy();

		for (ListItem<T> const* ptr = list.head; ptr != nullptr; ptr = ptr->next)
			addAtTail(ptr->data);
	}

	return *this;
}

template <class T>
void LinkedList<T>::removeFromHead()
{
	try {
		if (head == nullptr)
			throw ListException();

		T  res = head->data;

		const ListItem<T>* tmp = head;

		if (head == tail)
			tail = nullptr;

		head = head->next;
		delete tmp;
	}
	catch (ListException &le)
	{
		le.handle("EROARE!\n Lista este vida");
	}
}

template <class T>
void LinkedList<T>::removeFromTail()
{
	try {
		if (tail == nullptr)
			throw ListException();

		T res = tail->data;
		ListItem<T>* tmp = head;

		if (head == tail)
			tail = head = nullptr;
		else
		{
			while (tmp->next != tail)
			{
				tmp = tmp->next;
			}

			tail = tmp;
			tmp = tail->next;
			tail->next = nullptr;
		}
		delete tmp;
	}
	catch(ListException & le)
	{
		le.handle("EROARE!\n Lista este vida!");
	}
}

template <class T>
void LinkedList<T>::extract(T const& item)
{
	ListItem<T>* ptr = head;
	ListItem<T>* prevPtr = nullptr;

	while(ptr!=nullptr && ptr->data!=item)
	{
		prevPtr = ptr;
		ptr = ptr->next;
	}

	try {
		if (ptr == nullptr)
			throw ListException();
	}
	catch(ListException& li)
	{
		li.handle("EROARE!\nValoarea introdusa nu a fost gasita\n");
	}

	if (ptr == head)
		head = ptr->next;
	else
		prevPtr->next = ptr->next;
	if (ptr == tail)
		tail = prevPtr;

	delete ptr;
}

template <class T>
void LinkedList<T>::insertAfter(ListItem<T> * arg, T const& item)
{
	ListItem<T>* ptr = static_cast<ListItem<T>*>(arg);
	try
	{
		if (ptr == nullptr)
			throw ListException();


		ListItem<T>* tmp = new ListItem<T>(item, ptr->next);
		ptr->next = tmp;
		if (tail == ptr)
			tail = tmp;
	}
	catch (ListException& le)
	{
		le.handle("EROARE!\nPozitia este invalida!");
	}
}

template <class T>
void LinkedList<T>::insertBefore(ListItem<T>* arg, T const& item)
{
	ListItem<T>* ptr = static_cast<ListItem<T>*>(arg);

	try {
		if (ptr == nullptr)
			throw ListException();


		ListItem<T>* tmp = new ListItem<T>(item, ptr);
		if (head == ptr)
			head = tmp;
		else
		{
			ListItem<T>* prevPtr = head;
			while (prevPtr != nullptr && prevPtr->next != ptr)
				prevPtr = prevPtr->next;

			if (prevPtr == nullptr)
				throw ListException();
			prevPtr->next = tmp;
		}
	}
	catch (ListException& le)
	{
		le.handle("EROARE!\n Pozitia este invalida!");
	}
}

template <class T>
T& LinkedList<T>::removeAfter(ListItem<T> * arg)
{
	try {
		if (arg == nullptr)
			throw ListException();
		if (arg->next == nullptr)
			throw ListException();
		ListItem<T>* ptr = arg->next;
		arg->next = ptr->next;

		if (tail == ptr)
			tail = arg;
		T res = ptr->data;
		delete ptr;
		return res;
	}
	catch(ListException &le)
	{
		le.handle("EROARE!Lista fie este vida, fie s-a incercat eliminarea elementului situat dupa ultimul element!");
	}
}

//Inverseaza o lista simplu inlantuita
template <class T>
LinkedList<T>& LinkedList<T>::reverse()
{
	//Elementul curent
	ListItem<T>* curr = head;
	//Elementul precedent
	ListItem<T>* prev = nullptr;
	//Elementul urmator
	ListItem<T>* next = nullptr;


	while(curr!=nullptr)
	{
		//Stocam urmatorul element
		next = curr->next;
		//Inversam adresa elementului curent cu cea a celui precedent
		curr->next = prev;

		//Trecem la urmatorul element
		prev = curr;
		curr = next;
	}

	//Resetam valoarea head-ului
	head = prev;

	//Returnam adresa obiectului curent
	return*this;
}

//Separa o lista simplu inlantuita in doua liste inlantuite astfel incat nodurile primei liste sa mearga alternant in cele doua liste.
template <class T>
LinkedList<T>* LinkedList<T>::split()
{
	LinkedList<T> *result=new LinkedList<T>[2];
	//Copie a obiectului curent
	LinkedList<T>current = (*this);
	LinkedList<T>l1, l2;
	//Pentru a face separarea, astfel incat nodurile listei initiale sa mearga alternand in cele 2 liste, vom folosi un contor.
	//Cand valoarea contorului este una para, se vor insera valori in prima lista. In caz contrar,in cea de-a doua
	int counter = 0;
	while(!current.isEmpty())
	{
		if (counter % 2 == 0) {
			T value = current.getFirst();
			current.removeFromHead();
			l1.addAtTail(value);
		}
		else
		{
			T value = current.getFirst();
			current.removeFromHead();
			l2.addAtTail(value);
		}

		counter++;

		*result = l1;
		*(result + 1) = l2;
	}
	return result;
}

//Elimina elementele duplicate din lista
template <class T>
void LinkedList<T>::removeDuplicates()
{

	//Folosim o tabela de dispersie pentru o stoca valorile de frecventa 1 din lista simplu inlantuita
	unordered_set<T>seen;
	ListItem<T>* current = this->getHead();
	ListItem<T>* previous = nullptr;

	while(current!=nullptr)
	{
		//Daca variabila current este regasita in setul seen, atunci o eliminam din lista
		if(seen.find(current->getData())!=seen.end())
		{
			previous->next = current->next;
			delete current;
		}
		//Altfel, o inseram in set, pentru a ii tine evidenta
		else
		{
			seen.insert(current->data);
			previous = current;
		}

		current = previous->next;
	}
}

//Sorteaza lista in ordine crescatoare
template <class T>
void LinkedList<T>::sortAscending()
{
	if (this->isEmpty()) {
		cout << "Lista este vida!\n";
		return;
	}

	ListItem<T>* current = this->getHead();
	ListItem<T>* incoming = nullptr;
	T aux;

	while(current!=nullptr)
	{
		incoming = current->next;

		while (incoming!=nullptr)
		{
			if(current->data>incoming->data)
			{
				aux = current->data;
				current->data = incoming->data;
				incoming->data = aux;
			}
			incoming = incoming->next;
		}
		current = current->next;

	}
}

//Adauga valori in lista simplu inlantuita in asa fel incat aceasta sa se pastreze sortata crescator
template <class T>
void LinkedList<T>::addValue(T val)
{
	ListItem<T>* prevPtr = nullptr;
	ListItem<T>* ptr = this->getHead();
	while (ptr != nullptr && val > ptr->getData())
	{
		prevPtr = ptr;
		ptr = ptr->getNext();
	}

	if (prevPtr == nullptr)
		this->addAtHead(val);
	else
		this->insertAfter(prevPtr, val);
}

//Interclaseaza doua liste simplu inlantuite
template <class T>
LinkedList<T> LinkedList<T>::merge(LinkedList<T> l)
{
	LinkedList<T>copy = (*this);
	LinkedList<T> result;
	try {
		if (copy.isEmpty() && l.isEmpty())
			throw ListException();
	}
	catch (ListException& le)
	{
		le.handle("EROARE!\n Cele 2 liste sunt vide, nu se poate realiza interschimbarea!");
		return result;
	}

	if (copy.isEmpty())
		return l;
	if (l.isEmpty())
		return copy;

	//Ne asiguram ca listele sunt sortate inainte de interclasare
	copy.sortAscending();
	l.sortAscending();

	result = copy;
	for (ListItem<T>* ptr = l.getHead(); ptr != nullptr; ptr = ptr->next)
		//Utilizam functia addValue(), anterior definita, pentru a ne asigura ca lista rezultata in urma interclasarii, va fi si ea sortata
		result.addValue(ptr->getData());

	//Returnam rezultatul
	return result;
}

//Cauta valoarea val in lista curenta. In cazul in care valoarea exista in lista returneaza true, in caz contrar, false
template <class T>
bool LinkedList<T>::find(T const& val)
{
	//Daca lista este vida, este clar ca valoarea val nu poate fi gasita in lista
	if (this->isEmpty())
		return false;

	//Daca lista are un singur element, verificam daca acel element este echivalentu cu parametrul pasat metodei
	if (this->head == this->tail)
		if (this->head->getData() == val)
			return true;

	//Parcurgem lista pana la final sau pana la gasirea valorii cautate
	ListItem<T>* pointer = this->getHead();
	while (pointer != nullptr && pointer->data!=val)
		pointer = pointer->getNext();

	//Am gasit elementul in lista
	if (pointer != nullptr)
		return true;
	//Daca am ajuns la final si nu am gasit elementul, este evident ca acesta nu se regaseste in lista
	return false;
}

//Calculeaza intersectia a doua liste simplu inlantuite
template <class T>
LinkedList<T> LinkedList<T>::intersect(LinkedList<T> l)
{

	LinkedList<T>copy = (*this);
	LinkedList<T>result;

	if (copy.isEmpty() && l.isEmpty()) {
		cout << "Listele sunt vide!\n";
		return result;
	}
		

	for (ListItem<T>* ptr = l.getHead(); ptr != nullptr; ptr = ptr->next)
		if (copy.find(ptr->getData()))
			result.addAtTail(ptr->getData());

	return result;
}


//Functie utilitara, utilizata de functia ce utilizeaza algoritmul radixSort.
//Aceasta functie cauta si returneaza elementul de valoare maxima dintr-o instanta a clasei Array.
//Intrucat functia realizeaza o singura trecere prin array-ul parametru arr, cu n elemente, ordinul timpului de executie al functiei este echivalent cu O(n).
template<class T>
T getMax(Array<T>const& arr)
{
	T maximum=INT_MIN;

	for (int i = 0; i < arr.getSize(); i++)
		if (arr[i] > maximum)
			maximum = arr[i];

	return maximum;
}

//Pentru a implementa algoritmul radix Sort, vom avea nevoie de sortarea prin numarare. Pentru acesata, vom implementa, pentru vectorul arr, pasat prin referinta drept parametru al functiei, algoritmul de sortare prin numarare, tinand cont de cifra stocata in variabila digit
template <class T>
void countSort(Array<T>& arr, int digit)
{
	//Vectorul in care vom stoca rezultatul sortarii
	Array<int>output(arr.getSize());
	int i;
	Array<int>freq(10);
	//Count va fi un vector de frecvente in care se vor stoca numarul aparitiilor cifrelor din vectorul arr, pasat drept parametru
	for (i = 0; i < 10; i++)
		freq[i] = 0;

	//Stocam numarul aparitiilor cifrelor din vectorul parametru in vectorul count
	for (i = 0; i < arr.getSize(); i++)
		freq[(arr[i] / digit) % 10]++;

	//Modificam aranjarea elementelor din count[i], astfel incat vectorul count sa contina si pozitia aferenta cifrei din vectorul output
	for (i = 1; i < 10; i++)
		freq[i] += freq[i - 1];

	//Construim array-ul sortat

	for (i = arr.getSize() - 1; i >= 0; i--) {
		output[freq[(arr[i] / digit) % 10] - 1] = arr[i];
		freq[(arr[i] / digit) % 10]--; //odata ce am inserat elementul, scadem frecventa acestuia
	}

	//Copiem array-ul output in arr, astfel incat vectorul pasat drept parametru sa contina numerele sortate, in functie de valoarea cifrei curente stocata in parametrul digit
	for (i = 0; i < arr.getSize(); i++)
		arr[i] = output[i];
}

//Nu in ultimul rand, functia ce implementeaza algoritmul radix sort, ce face apel la cele 2 functii anterior definite
//Ordinul timpului de executie :O(n).
template <class T>
void radixSort(Array<T>& arr)
{
	//Identifica elementul maxim din array pentru a cunoaste numarul maxim de cifre pentru cel mai mare element din sir
	int maximum = getMax(arr);

	//Apelam functia count sort,pentru fiecare cifra a fiecarui numar din array. A se observa faptul ca valoarea digit este pasata functiei, in locul cifrei curente pentru fiecare numar in parte. Pentru fiecare iteratie, variabila digit devine 10^i, unde i reprezinta pozitia in numar a cifrei (considerand 0 drept pozitia cifrei 1).
	for(int digit=1;maximum/digit>0;digit*=10)
	{
		countSort(arr, digit);
	}
}

//Sorteaza o lista simplu inlantuita la citire, intr-un timp de executie O(n), utilizand un array auxiliar si un algoritm de sortatre al carui timp estimativ de executie aproximativ este O(n) (radix sort).
template <class T>
void LinkedList<T>::readWhileSorting()
{
	//Numar elemente de introdus
	unsigned int n;
	cout << "Cate elemente doriti sa introduceti in lista?";
	cin >> n;
	//Array auxiliar in care vom stoca si vom sorta elementele ce vor urma a fi adaugate in lista simplu inlantuita
	Array<T>temp(n);
	T current;

	for(int i=0;i<n;i++)
	{
		cout << "Elementul " << i + 1 << ": ";
		cin >> current;
		temp[i] = current;
	}

	//Sortam array-ul auxiliar crescator utilizand un algoritm de sortare al carui timp de executie este echivalent cu O(n).
	radixSort(temp);

	//Parcurgem array-ul sortat si introducem fiecare element la sfarsitul sau inceputul listei stocate in obiectul ce apeleaza metoda (rezultatul va fi identic indiferent de regiunea din lista unde se va alege a se face inserarea, intrucat array-ul temp este deja sortat).
	for (int i = 0; i < temp.getSize(); i++)
		this->addAtTail(temp[i]);


}



#pragma endregion