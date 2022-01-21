//Fisier SortedLinkedList.h, contine implementarea clasei SortedLinkedList, care nu este nimic altceva decat o implementare a unei liste simple inlantuite cu valori sortate (valori presupuse comparabile)
#pragma once
#include "LinkedList.h"
#include "Container.h"

//Clasa  generica SortedLinkedList, mosteneste clasa abstracta container
template <class T>
class SortedLinkedList :public Container
{
	//Lista-suport
	LinkedList<T>list;

public:

	//Constructor de initializare, initializeaza lista-suport cu o lista vida, iar membrul count al clasei Container, cu 0
	SortedLinkedList():list()
	{
		count = 0;
	}

	//Constructor de copiere, permite copierea listei sl in instanta curenta
	SortedLinkedList(SortedLinkedList const& sl)
	{
		this->list = sl.list;
		this->count = sl.count;
	}

	//Adauga o valoare la lista sortata
	void addValue(T val);

	//Elimina o valoare din lista sortata, nealterand lista
	void removeValue(T val);

	//Cauta o valoare in lista sortata
	ListItem<T>* findValue(T val);

	//Obtine numarul de elemente al listei sortate
	unsigned getCount() const override;

	//Verifica daca lista este sau nu goala
	bool isEmpty() const override;

	//Dezaloca spatiul ocupat de lista sortata curenta
	void Destroy();

	//Obtine primul element din lista suport a listei sortate
	T const& getFirst() const;

	//Obtine ultimul element din lista suport a listei sortate
	T const& getLast() const;

	//Obtine adresa de memorie a primului nod al listei suport
	ListItem<T>* getHead();

	//Obtine adresa de memorie al ultimului nod al listei suport
	ListItem<T>* getTail();

	//Setter pentru membrul count al clasei abstracte Container
	void setCount(int Count);

	//Elimina ultimul element din lista sortata
	void removeFromTail();

	//Interclaseaza doua liste simplu inlantuite sortate
	SortedLinkedList<T> merge(SortedLinkedList<T> sl);

private:
	//Verifica daca lista este sau nu plina
	 bool isFull() const override;

public:

	//Supraincarcarea operatorului de scriere in fluxul de intrare, permite citirea de la tastatura a elementelor ce vor urma a fi inserate in lista sortata, pe masura ce acestea vor fi adaugate in lista
	friend istream& operator >>(istream& istr, SortedLinkedList<T> &sl)
	{
		unsigned int els;
		T val;
		cout << "Cate elemente se vor insera in lista sortata? "; istr >> els;
		for(int i=0;i<els;i++)
		{
			cout << "Elementul " << i + 1 << ": "; istr >> val;
			if (val >= sl.list.getLast())
				sl.list.addAtTail(val);
			if (sl.list.getHead() == nullptr)
				sl.list.addAtHead(val);
			if (sl.list.getFirst() >= val)
				sl.list.addAtHead(val);
			T prev = val;


		}
		return istr;
	}

	//Supraincarcarea operatorului de scriere in fluxul de iesire permite afisarea pe ecran a listei simplu inlantuite sortate
	friend ostream& operator << (ostream& ostr,SortedLinkedList<T> sl)
	{
		if (sl.isEmpty()) {
			ostr << "Lista sortata este goala!\n";
			return ostr;
		}
		ostr << sl.list;
		return ostr;
	}

};

//Definitii metode clasa SortedLinkedList
//Adauga o valoare la lista sortata
template <class T>
void SortedLinkedList<T>::addValue(T val)
{
	ListItem<T>* prevPtr = nullptr;
	ListItem<T>* ptr = list.getHead();
	while(ptr!=nullptr && val<ptr->getData())
	{
		prevPtr = ptr;
		ptr = ptr->getNext();
	}

	if (prevPtr == nullptr)
		list.addAtHead(val);
	else
		list.insertAfter(prevPtr, val);
	count++;
}

//Elimina o valoare din lista sortata
template <class T>
void SortedLinkedList<T>::removeValue(T val)
{
	ListItem<T>* prevPtr = nullptr;
	ListItem<T>* ptr = list.getHead();

	if (findValue(val) == nullptr)
		return;

	//val<ptr->getData()

	while(ptr!=nullptr && val < ptr->data)
	{
		prevPtr = ptr;
		ptr = ptr->next;
	}

	if (prevPtr == nullptr)
		list.removeFromHead();
	else
		list.removeAfter(prevPtr);

	count--;

}

//Cauta o valoare in lista sortata
template <class T>
ListItem<T>* SortedLinkedList<T>::findValue(T val)
{
	ListItem<T>* pointer = list.getHead();
	while (pointer != nullptr && pointer->data.equals(val)==false)
		pointer = pointer->getNext();
	return pointer;
}

//Verifica daca lista sortata este sau nu goala
template <class T>
bool SortedLinkedList<T>::isEmpty() const
{
	return list.isEmpty();
}

//Obtine numarul elementelor din lista sortata
template <class T>
unsigned SortedLinkedList<T>::getCount() const
{
	
	return count;
}

//Intrucat isFull din clasa container este o functie virtuala pura, vom returna mereu false pentru metoda isFull in cazul clasei SortedLinkedList, intrucat lista este alocata dinamic
template <class T>
bool SortedLinkedList<T>::isFull() const
{
	return false;
}

//Dezaloca spatiul ocupat de lista sortata curenta
template <class T>
void SortedLinkedList<T>::Destroy()
{
	list.Destroy();
}

//Obtine primul element din lista suport a listei sortate
template <class T>
T const& SortedLinkedList<T>::getFirst() const
{
	return list.getFirst();
}

//Obtine ultimul element din lista suport a listei sortate
template <class T>
T const& SortedLinkedList<T>::getLast() const
{
	return list.getLast();
}

//Obtine adresa de memorie a primului nod al listei suport
template <class T>
ListItem<T>* SortedLinkedList<T>::getHead()
{
	return list.getHead();
}

//Obtine adresa de memorie a primului nod al listei suport
template <class T>
ListItem<T>* SortedLinkedList<T>::getTail()
{
	return list.getTail();
}

//Seteaza numarul de elemente din lista sortata
template <class T>
void SortedLinkedList<T>::setCount(int Count)
{
	this->count = Count;
}

template <class T>
void SortedLinkedList<T>::removeFromTail()
{
	list.removeFromTail();
}

//Interclaseaza doua liste simplu inlantuite sortate
template <class T>
SortedLinkedList<T> SortedLinkedList<T>::merge(SortedLinkedList<T> sl)
{
	SortedLinkedList<T>copy = (*this);
	SortedLinkedList<T> result;
	try {
		if (copy.isEmpty() && sl.isEmpty())
			throw ListException();
	}
	catch (ListException &le)
	{
		le.handle("EROARE!\n Cele 2 liste sunt vide, nu se poate realiza interschimbarea!");
		return result;
	}

	if (copy.isEmpty())
		return sl;
	if (sl.isEmpty())
		return copy;

	result = copy;
	for (ListItem<T>* ptr = sl.getHead(); ptr != nullptr; ptr = ptr->next)
		result.addValue(ptr->getData());

	return result;

}

















