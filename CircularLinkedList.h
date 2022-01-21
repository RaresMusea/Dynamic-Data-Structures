//Fisier CircularLinkedList.h->Contine clasa necesara definirii si implementarii principalelor operatii referitoare la structura de lista simplu inlantuita circulara

#pragma once
#include "Exceptions.h"
#include <iostream>
using namespace std;

template <class T>
class CircularLinkedList; //Prototipul clasei generice CircularLinkedList


//Clasa generica ListItem, se refera la un element al unei liste inlantuite
template <class T>
class ListItem
{

protected:
	T data;
	ListItem* next = nullptr;


public:

	//Constructor inline de initializare, seteaza informatia din nodul curent al listei si adresa de memorie al urmatorului element al acesteia
	ListItem(T const& Data, ListItem<T>* Next) :data(Data), next(Next) {}

	//Obtine informatia din nodul curent al listei
	T const& getData() const;

	//Obtine informatia din urmatorul nod al listei
	ListItem* getNext() const;

	//Seteaza informatia din nodul curents
	void setData(T Data);

	//Seteaza adresa de memorie a urmatorului element
	void setNext(ListItem* Next);

	//Clasa LinkedList va avea acces la variabilele membru ale acestei clase
	friend CircularLinkedList<T>;

};

//Definitii metode ListItem:
//Obtine informatia din nodul curent al listei
template <class T>
T const& ListItem<T>::getData() const
{
	return data;
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


//Definitia clasei generice CircularLinkedList, implementeaza structura de tip Lista circulara
template <class T>
class CircularLinkedList
{
	//Retin adresele inceputului, respectiv sfarsitului listei
	ListItem<T>* head;
	ListItem<T>* tail;

public:

	//Constructor inline implicit, seteaza head si tail cu valoarea nullptr
	CircularLinkedList() :head(nullptr), tail(nullptr) {}

	//Constructor inline de copere, permite copierea unei liste pasate ca si parametru in obiectul curent
	CircularLinkedList(CircularLinkedList<T> const& list) :head(nullptr), tail(nullptr)
	{
		ListItem<T> *i;
		for (i = list.head; i != list.tail; i = i->next)
		{
			addAtTail(i->data);
		}

		addAtTail(i->data);
	}

	//Dealoca memoria ocupata de o lista circulara
	void Destroy();

	//Destructorul,apeleaza metoda Destroy
	~CircularLinkedList() { //Destroy();
	}

	//Obtine primul element al listei circulare
	ListItem<T>* getHead() const;

	//Obtine elementul de la sfarsitul listei circulare
	ListItem<T>* getTail() const;

	//Verifica daca lista circulara este sau nu populata cu elemente
	bool isEmpty() const;

	//Adauga un nod nou, la inceputul listei circulare
	void addAtHead(T const& item);

	//Adauga un nod nou, la sfarsitul listei circulare
	void addAtTail(T const& item);

	//Obtine primul element al listei circulare
	T const& getFirst() const;

	//Obtine ultimul element al listei circulare
	T const& getLast() const;

	//Operatorul de atribuire, permite copierea unei liste circulare in o alta
	CircularLinkedList<T>& operator = (CircularLinkedList<T> const& list);

	//Elimina primul element al listei circulare
	void removeFromHead();

	//Elimina ultimul element al listei circulare
	void removeFromTail();

	//Elimina elementul item din lista circulara
	void erase(T const& item);

	//Insereaza in lista circulara un nou element dupa elementul specificat
	void insertAfter(ListItem<T>* arg, T const& item);

	//Insereaza in lista un nou element inaintea elementului specificat
	void insertBefore(ListItem<T>* arg, T const& item);

	//Elimina din lista circulara elementul pozitionat in aceasta dupa nodul pasat drept parametru
	T& removeAfter(ListItem<T>* arg);

	//Concateneaza doua liste circulare, creand o noua lista circulara. 
	CircularLinkedList<T> concatenate(CircularLinkedList const& cl);

	//Obtine adresa de memorie a urmatorului nod al listei circulare
	ListItem<T>* getNextNode(ListItem<T>* node);

	//Separa o lista circulara in doua subliste circulare, care contine nodurile alternante ale listei initiale
	CircularLinkedList<T>* split();


	//Supraincarcarea operatorului de scriere in fluxul de iesire, permite afisarea pe ecran a continutului listei circulare
	friend ostream& operator << (ostream& ostr, CircularLinkedList<T> li)
	{
		if (li.isEmpty()) {
			ostr << "Lista este goala!\n";
			return ostr;
		}

		ListItem<T>* ptr = li.head;
		while (ptr!=li.tail)
		{
			ostr<< ptr->getData()<< '\t';
			ptr = ptr->getNext();
			
		}

		ostr<<ptr->getData() << '\t';
		return ostr;
	}
};

//Definitii Metode clasa LinkedList
//Dealoca memoria ocupata de o lista circulara
template <class T>
void CircularLinkedList<T>::Destroy()
{
	while (head)
	{
		const ListItem<T>* aux = head;
		head = head->next;
		delete aux;
	}

	tail = nullptr;
}

//Obtine primul element al listei circulare
template <class T>
ListItem<T>* CircularLinkedList<T>::getHead() const
{
	return head;
}

//Obtine elementul de la sfarsitul listei circulare
template <class T>
ListItem<T>* CircularLinkedList<T>::getTail() const
{
	return tail;
}

//Verifica daca lista circulara este sau nu populata cu elemente
template <class T>
bool CircularLinkedList<T>::isEmpty() const
{
	return (head == nullptr);
}

//Adauga un nod nou, la inceputul listei circulare
template <class T>
void CircularLinkedList<T>::addAtHead(T const& item)
{
	ListItem<T>* tmp = new ListItem<T>(item, head);
	if (head == nullptr) {
		tail = tmp;
		tail->next = head;
	}
	head = tmp;

}

//Adauga un nod nou, la sfarsitul listei circulare
template <class T>
void CircularLinkedList<T>::addAtTail(T const& item)
{
	ListItem<T>* aux = new ListItem<T>(item, head);

	if (head == nullptr)
		head = aux;
	else
		tail->next = aux;
	tail = aux;
	tail->next = head;

}

//Obtine primul element al listei circulare
template <class T>
T const& CircularLinkedList<T>::getFirst() const
{
	try {
		if (head == nullptr)
			throw ListException();
		return head->data;
	}
	catch (ListException& le)
	{
		le.handle("EROARE!\nLista este goala!");
	}
}

//Obtine ultimul element al listei circulare
template <class T>
T const& CircularLinkedList<T>::getLast() const
{
	try {
		if (tail == nullptr)
			throw ListException();
		return tail->data;
	}
	catch (ListException& le)
	{
		le.handle("EROARE!\nLista este goala!");
	}
}

//Copierea unei liste circulare in alta
template <class T>
CircularLinkedList<T>& CircularLinkedList<T>::operator = (CircularLinkedList<T> const& list)
{
	if (&list != this)
	{
		Destroy();

		for (ListItem<T> const* ptr = list.head; ptr != list.tail; ptr = ptr->next)
			addAtTail(ptr->data);
	}
	addAtTail(list.tail->data);

	return *this;
}

//Elimina primul element din lista circulara
template <class T>
void CircularLinkedList<T>::removeFromHead()
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

//Elimina ultimul element al listei circulare
template <class T>
void CircularLinkedList<T>::removeFromTail()
{
	try {
		if (tail == nullptr)
			throw ListException();

		T res = tail->data;
		ListItem<T>* tmp = head;

		if (head == tail) {
			tail->next = nullptr;
			tail = head = nullptr;
		}
		else
		{
			while (tmp->next != tail)
			{
				tmp = tmp->next;
			}

			tail = tmp;
			tmp = tail->next;
			tail->next = head;
		}
		delete tmp;
	}
	catch (ListException& le)
	{
		le.handle("EROARE!\n Lista este vida!");
	}
}


//Insereaza in lista circulara un nou element dupa nodul specificat
template <class T>
void CircularLinkedList<T>::insertAfter(ListItem<T>* arg, T const& item)
{
	ListItem<T>* ptr = static_cast<ListItem<T>*>(arg);
	try
	{
		if (ptr == nullptr)
			throw ListException();


		ListItem<T>* tmp = new ListItem<T>(item, ptr->next);
		ptr->next = tmp;
		if (tail == ptr) {
			tail = tmp;
			tail->next = head;
		}
	}
	catch (ListException& le)
	{
		le.handle("EROARE!\nPozitia este invalida!");
	}
}

//Insereaza in lista circulara un nou element inainte de nodul specificat
template <class T>
void CircularLinkedList<T>::insertBefore(ListItem<T>* arg, T const& item)
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

//Sterge din lista speciala nodul situat dupa nodul specificat (daca exista)
template <class T>
T& CircularLinkedList<T>::removeAfter(ListItem<T>* arg)
{
	try {
		if (arg == nullptr)
			throw ListException();
		if (arg->next == nullptr)
			throw ListException();
		ListItem<T>* ptr = arg->next;
		arg->next = ptr->next;

		if (tail == ptr) {
			tail = arg;
			tail->next = head;
		}
		T res = ptr->data;
		delete ptr;
		return res;
	}
	catch (ListException& le)
	{
		le.handle("EROARE!Lista fie este vida, fie s-a incercat eliminarea elementului situat dupa ultimul element!");
	}
}

//Sterge din lista circulara nodul cu valoarea item (daca acesta poate fi gasit in lista)
template <class T>
void CircularLinkedList<T>::erase(T const& item)
{
	ListItem<T>* ptr = head;
	ListItem<T>* prevPtr = tail;

	try {

	//Cautam valoarea de eliminat pana la tail-ul listei. In cazul in care se ajunge acolo, si nu a fost gasita, ori ptr este nullptr, semn ca lista este vida este evident ca valoarea cautata nu poate fi gasita in lista circulara, deci eliminarea valorii respective va esua
	while (ptr != tail && ptr->data != item)
	{
		prevPtr = ptr;
		ptr = ptr->next;
	}
	if (ptr == tail || ptr==nullptr)
		throw ListException();


	}
	catch (ListException& li)
	{
		li.handle("EROARE!\nValoarea introdusa nu a fost gasita\n");
		return;
	}

	//Cazul contrar:iteratia while a luat sfarsit inainte ca ptr sa ajunga la tail:elementul a fost gasit
	if (ptr == head)
		head = ptr->next;
	else
		prevPtr->next = ptr->next;
	if (ptr == tail) {
		tail = prevPtr;
		tail->next = head; //Ultimul element cunoaste adresa primului, existand o legatura intre ele
	}

	delete ptr;
}

//Concateneaza 2 liste circulare creand o noua lista circulara
template <class T>
CircularLinkedList<T> CircularLinkedList<T>::concatenate(CircularLinkedList<T> const& cl)
{
	//Copiem in lista rezultanta lista circulara ce apeleaza metoda (obiectul curent)
	CircularLinkedList<T> result=*this;

	//Parcurgem a doua lista circulara, adaugand fiecare element la finalul listei rezultante
	for(ListItem<T>*i=cl.head;i!=cl.tail;i=i->next)
	{
		result.addAtTail(i->data);
	}

	//Adaugam ultimul element la lista rezultanta
	result.addAtTail(cl.tail->data);
	result.tail->next = head;

	return result;
}

template <class T>
ListItem<T>* CircularLinkedList<T>::getNextNode(ListItem<T>* node)
{
	ListItem<T>* ptr = static_cast<ListItem<T>*>(node);
	try {
		if (ptr==nullptr)
		{
			throw ListException();
		}

		ptr = ptr->next;
		return ptr;
	}

	catch(ListException &le)
	{
		le.handle("EROARE!\nLista sau parametru invalid!");
	}
	
}


//Separa o lista circulara in doua subliste circulare, care contine nodurile alternante ale listei initiale
template <class T>
CircularLinkedList<T>* CircularLinkedList<T>::split()
{
	CircularLinkedList<T>* result = new CircularLinkedList<T>[2];
	CircularLinkedList<T> cl1, cl2;
	CircularLinkedList<T>copy=*this;

	//Vom utiliza un contor pentru a separa nodurile listei initiale
	//Pentru valori pare ale contorului, se vor insera valori in prima sublista circulara
	//Pentru valori impare ale contorului, se vor insera valori in a doua sublista circulara

	int count = 0;
	ListItem<T>*ptr = copy.head;

	while (ptr!=copy.tail)
	{
		if(count%2==0)
		{
			T value = ptr->getData();
			ptr=ptr->getNext();
			cl1.addAtTail(value);
		}
		else
		{
			T value = ptr->getData();
			ptr=ptr->getNext();
			cl2.addAtTail(value);
		}
		count++;
	}

	if(count%2==0)
	{
		T value = ptr->getData();
		cl1.addAtTail(value);
	}
	else
	{
		T value = ptr->getData();
		cl2.addAtTail(value);
	}
	
	*result = cl1;
	*(result + 1) = cl2;
	return result;
}



#pragma endregion