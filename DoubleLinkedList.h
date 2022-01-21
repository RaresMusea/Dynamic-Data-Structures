//Fisier DoubleLinkedList.h->Contine definitia clasei DoubleLinkedListItem, care figureaza un nod al unei liste dublu inlantuite, cat si operatiile caracteristice asupra acestora, alaturi de clasa DoubleLinkedList, care utilizeaza clasa anterior mentionata in vederea implementarii structurii de lista dublu inlantuita, cat si a operatiilor elementare ce pot avea loc la nivelul acesteia.
#pragma once
#include <iostream>
#include "Exceptions.h" //Foloseste structura ListException, pentru structuri de date alocate dinamic
using namespace std;
template <class T>
class DoubleLinkedList; //declaratie anticipata a clasei DoubleLinkedList

//Clasa generica DoubleLinkedListItem, implementeaza conceptul de nod al listei dublu inlantuite
template <class T>
class DoubleLinkedListItem
{
	//Informatia din nodul curent
	T data;

	//Pointeri catre nodul urmator si precedent
	DoubleLinkedListItem* next, * previous;

public:

	//Constructor inline de initializare, seteaza informatia din nodul curent al listei si adresa de memorie a urmatorului si a precedentului element al acesteia
	DoubleLinkedListItem(T const& Data, DoubleLinkedListItem<T>* Next, DoubleLinkedListItem<T>* Previous) :data(Data), next(Next), previous(Previous){}

	//Obtine informatia din nodul curent al listei
	T const& getData() const;

	//Obtine adresa de memorie al urmatorului nod al listei
	DoubleLinkedListItem* getNext() const;

	//Obtine adresa de memorie al nodului precedent al listei
	DoubleLinkedListItem* getPrevious() const;

	//Clasa DoubleLinkedList va avea acces la variabilele membru ale acestei clase
	friend class DoubleLinkedList<T>;

};

//Definitii metode clasa DoubleLinkedListItem:

//Obtine informatia din nodul curent al listei
template <class T>
T const& DoubleLinkedListItem<T>::getData() const
{
	return data;
}

//Obtine adresa de memorie al urmatorului nod al listei
template <class T>
DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getNext() const
{
	return next;
}

//Obtine adresa de memorie al nodului precedent al listei
template <class T>
DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrevious() const
{
	return previous;
}

//Clasa generica DoubleLinkedList->contine implementarea structurii cunoscute si sub denumirea de lista dublu inlantuita, cat si a operatiilor elementare care pot avea loc la nivelul acestei structuri
template <class T>
class DoubleLinkedList
{
	//Adresa elementului de la inceputul listei
	DoubleLinkedListItem<T>* head;

	//Adresa nodului de la sfarsitul listei
	DoubleLinkedListItem<T>* tail;

public:

	//Constructor implicit:initializeaza lista vida (adresele de memorie ale lui head, respectiv tail vor pointa catre nullptr)
	DoubleLinkedList() :head(nullptr), tail(nullptr) {}

	//Constructor de copiere->Copiaza lista dublu inlantuita pasata ca si parametru in instanta curenta a clasei DoubleLinkedList.
	DoubleLinkedList(DoubleLinkedListItem<T> const dList) {
		head = nullptr, tail = nullptr;
		DoubleLinkedListItem<T>* ptr;
		for (ptr = dList.head; ptr != 0; ptr = ptr->next)
			addLast(ptr->data);
	}

	~DoubleLinkedList() { /* Destroy();*/ }

	//Copierea listelor
	DoubleLinkedList<T>& operator = (DoubleLinkedList<T> const& dl);

	//Dezaloca memoria ocupata de lista dublu inlantuita
	void Destroy();

	//Obtine adresa de memorie al primului nod al listei
	DoubleLinkedListItem<T>* getHead() const;

	//Obtine adresa de memorie al ultimului nod al listei
	DoubleLinkedListItem<T>* getTail() const;

	//Verifica daca lista curenta este sau nu vida
	bool isEmpty() const;

	//Obtine informatia stocata in primul nod al listei
	T const& getFirst() const;

	//Obtine informatia stocata in ultimul nod al listei
	T const& getLast() const;

	//Adauga un element drept prim element al listei
	void addFirst(T const& el);

	//Adauga un element drept ultim element al listei
	void addLast(T const& el);

	//Adauga un element in lista inaintea nodului pasat drept prim parametru
	void addBefore(DoubleLinkedListItem<T>* arg, T const& el);

	//Adauga un element in lista inaintea nodului pasat drept prim parametru
	void addAfter(DoubleLinkedListItem<T>* arg, T const& el);

	//Elimina primul element al listei (head)
	T& removeFirst();

	//Elimina ultimul element al listei (tail)
	void removeLast();

	//Elimina din lista nodul cu valoarea specificata drept parametru (daca exista)
	void extract(T const& value);

	//Cauta o valoare in lista dublu inlantuita. Daca o gaseste, returneaza adresa nodului ce contine valoarea. In caz contrar, nullptr
	DoubleLinkedListItem<T>* find(T const& value);

	//Modifica vechea valoarea a unui nod (pasata ca prim parametru) cu o noua valoare, pasata ca si parametru secund.
	void modifyNodeValue(T oldValue, T newValue);

	void readWhileSorting();

	//Supraincarcarea operatorului de scriere in fluxul de intrare permite citirea de la tastatura a unei liste dublu inlantuite
	friend istream& operator >> (istream& istr, DoubleLinkedList& dl)
	{
		unsigned int n;
		T el;
		cout << "Cate elemente doriti sa introduceti? "; istr >> n;
		for(int i=0;i<n;i++)
		{
			cout << "Elementul " << i + 1;
			istr >> el;
			dl.addLast(el);
		}

		return istr;
	}


	//Supraincarcarea operatorului de scriere in fluxul de iesire permite afisarea pe ecran a listei dublu inlantuite
	friend ostream& operator << (ostream& ostr, DoubleLinkedList dl)
	{

		while (!dl.isEmpty())
		{
			ostr << dl.getFirst() << '\t';
			dl.removeFirst();
		}
		return ostr;
	}

	//Afiseza lista pe ecran
	void print();

};

//Definitii metode clasa DoubleLinkedList:
template <class T>
void DoubleLinkedList<T>::Destroy()
{
	while (head)
	{
		DoubleLinkedListItem<T>* tmp = head;
		head = head->next;
		delete tmp;
	}
	tail = nullptr;
}

//Obtine adresa de memorie al primului nod al listei
template <class T>
DoubleLinkedListItem<T>* DoubleLinkedList<T>::getHead() const
{
	return head;
}

//Obtine adresa de memorie al ultimului nod al listei
template <class T>
DoubleLinkedListItem<T>* DoubleLinkedList<T>::getTail() const
{
	return tail;
}

//Verifica daca lista curenta este sau nu vida
template <class T>
bool DoubleLinkedList<T>::isEmpty() const
{
	return head == nullptr;
}

//Obtine informatia stocata in primul nod al listei
template <class T>
T const& DoubleLinkedList<T>::getFirst() const
{
	try {
		if (head == nullptr)
			throw ListException();
	}
	catch (ListException& le)
	{
		le.handle("EROARE!\n Lista este vida!");

	}
	return head->data;

}

//Obtine informatia stocata in ultimul nod al listei
template <class T>
T const& DoubleLinkedList<T>::getLast() const
{
	try {
		if (tail == nullptr)
			throw ListException();
	}
	catch (ListException& le)
	{
		le.handle("EROARE!\nLista este vida!");
	}
	return tail->data;
}

//Adauga un element drept prim element al listei
template <class T>
void DoubleLinkedList<T>::addFirst(T const& el)
{
	//Cream un nou nod
	DoubleLinkedListItem<T>* newnode = new DoubleLinkedListItem<T>(el, nullptr, head);
	if (head == nullptr)
		tail = newnode;
	else
		head->previous = newnode;
	head = newnode;
}

//Adauga un element drept ultim element al listei
template <class T>
void DoubleLinkedList<T>::addLast(T const& el)
{
	//Cream un nou nod
	DoubleLinkedListItem<T>* newnode = new DoubleLinkedListItem<T>(el, nullptr, tail);
	if (this->head == 0)
		this->head = newnode;
	else
		this->tail->next = newnode;
	this->tail = newnode;
}

//Adauga un element in lista inaintea nodului pasat drept prim parametru
template <class T>
void DoubleLinkedList<T>::addBefore(DoubleLinkedListItem<T>* arg, T const& el)
{

	DoubleLinkedListItem<T>* pointer = static_cast<DoubleLinkedListItem<T>*>(arg);

	try {
		if (pointer == nullptr)
			throw ListException();

		DoubleLinkedListItem<T>* tmp = new DoubleLinkedListItem<T>(el,arg, arg->previous);
		if (head == pointer) {
			head = tmp;
			pointer->previous = tmp;
		}
		else {
			DoubleLinkedListItem<T>* prevPtr = head;
			while (prevPtr != nullptr && prevPtr->next != pointer)
				prevPtr = prevPtr->next;
			if (prevPtr == nullptr)
				throw ListException();
			prevPtr->next = tmp;
			prevPtr->next->next->previous = tmp;
		}
	}
	catch (ListException& le) {
		le.handle("EROARE!\nPozitia este invalida!");
	}
}

//Adauga un element in lista dupa nodul pasat drept prim parametru
template <class T>
void DoubleLinkedList<T>::addAfter(DoubleLinkedListItem<T>* arg, T const& el)
{
	try {
		DoubleLinkedListItem<T>* pointer = static_cast<DoubleLinkedListItem<T>*>(arg);
		if (pointer == nullptr)
			throw ListException();
		DoubleLinkedListItem<T>* tmp = new DoubleLinkedListItem<T>(el, pointer->next,pointer);
		pointer->next = tmp;
		if (tail == pointer)
			tail = tmp;
	}
	catch (ListException& le) {
		le.handle("EROARE!\nPozitia este invalida!");
	}

}

//Elimina primul element din lista (head)
template <class T>
T& DoubleLinkedList<T>::removeFirst()
{
	try {
		if (head == nullptr)
			throw ListException();
		DoubleLinkedListItem<T>* pointer = head;
		if (tail == head)
			tail = head = nullptr;
		else {
			head = head->next;
			if (head == nullptr) {
				tail = nullptr;
				T res = pointer->data;
				delete pointer;
				return res;
			}
			head->previous = nullptr;
		}
		
		T res = pointer->data;
		delete pointer;
		return res;
	}
	catch (ListException& le)
	{
		le.handle("EROARE!\nLista este vida!");
	}
}

//Elimina ultimul element din lista (tail)
template <class T>
void DoubleLinkedList<T>::removeLast()
{
	try
	{
		if (tail == nullptr)
			throw ListException();
		DoubleLinkedListItem<T>* pointer = tail;
		if (tail == head)
			tail = head = nullptr;
		else
		{
			tail = tail->previous;
			tail->next = NULL;
		}
		delete pointer;
	}
	catch (ListException& le)
	{
		le.handle("ERAORE!\nLista este vida!");
	}
}

//Afiseaza lista
template <class T>
void DoubleLinkedList<T>::print()
{
	DoubleLinkedList<T> copy = *this;
	DoubleLinkedListItem<T>* ptr = copy.head;
	while (ptr!=nullptr)
	{
		std::cout << ptr->data << '\t';
		ptr = ptr->next;
	}
	std::cout << '\n';
}

//Copiaza o lista dublu inlantuita intr-o alta
template <class T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList<T> const& dl)
{
	if (&dl != this)
	{
		Destroy();

		for (DoubleLinkedListItem<T> const* ptr = dl.head; ptr != nullptr; ptr = ptr->next)
			addLast(ptr->data);
	}
	return *this;

}

//Cauta o valoare in lista dublu inlantuita. Daca o gaseste, returneaza adresa nodului ce contine valoarea. In caz contrar, nullptr
template <class T>
DoubleLinkedListItem<T>* DoubleLinkedList<T>::find(T const& value)
{
	try
	{
		if (this->isEmpty())
			throw ListException();
	}
	catch (ListException &le)
	{
		le.handle("EROARE!\n Lista este vida!");
		return nullptr;
	}

	DoubleLinkedList<T>copy = *this;
	DoubleLinkedListItem<T>* ptr = copy.head;

	while(ptr!=nullptr && ptr->data!=value)
	{
		ptr = ptr->next;
	}

	try {
		if (ptr == nullptr)
		{
			throw ListException();
		}
	}
	catch (ListException& le) {
		le.handle("Valoarea cautata nu a putut fi gasita!\n");
	}

	return ptr;

}

//Elimina din lista dublu inlantuita nodul ce contine elementul cu valoarea egala cu cea pasata drept parametru (in situatia in care acesta exista)
template <class T>
void DoubleLinkedList<T>::extract(T const& value)
{
	DoubleLinkedListItem<T>* ptr = head;
	DoubleLinkedListItem<T>* prevPtr = nullptr;

	while (ptr != nullptr && ptr->data != value)
	{
		prevPtr = ptr;
		ptr = ptr->next;
	}

	try {
		if (ptr == nullptr)
			throw ListException();
	}
	catch (ListException& li)
	{
		li.handle("EROARE!\nValoarea introdusa nu a fost gasita\n");
	}

	if (ptr == head) {
		head = ptr->next;
		head->previous = nullptr;
	}
	else {
		prevPtr->next = ptr->next;
		ptr->next->previous = prevPtr;
	}
	if (ptr == tail)
		tail = prevPtr;

	delete ptr;

}

//Modifica vechea valoarea a unui nod (pasata ca prim parametru) cu o noua valoare, pasata ca si parametru secund.
template <class T>
void DoubleLinkedList<T>::modifyNodeValue(T oldValue, T newValue)
{
	//Gasim vechea valoare
	DoubleLinkedListItem<T>*node=this->find(oldValue);
	//Modificam valoarea
	node->data = newValue;
}




