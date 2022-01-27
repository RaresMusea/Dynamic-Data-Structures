//Fisier BinarySearchTreeWithParentPointer->implementeaza conceptul de arbore binar de cautare, in cazul caruia, fiecare nod are un pointer ce retine adresa de memorie al nodului parinte
#pragma once
#include <iostream>
template <class T>
class BinarySearchTreeWithParentPointer {

	//Cheia
	T data;

	//Nodul parinte
	BinarySearchTreeWithParentPointer<T>* parent;

	//Subarborele stang
	BinarySearchTreeWithParentPointer<T>* left;

	//Subarborele drept
	BinarySearchTreeWithParentPointer<T>* right;

public:
	//Constructor implicit
	BinarySearchTreeWithParentPointer() { parent = nullptr; left = nullptr; right = nullptr; }

	//Constructor de initializare->Initializeaza un nod cu valoarea pasata drept parametru
	BinarySearchTreeWithParentPointer(T key):data(key), parent(nullptr), left(nullptr), right(nullptr) {}

	//Obtine adresa de memorie a nodului parinte
	BinarySearchTreeWithParentPointer* getParent()
	{
		return parent;
	}

	//Obtine subarborele stang
	BinarySearchTreeWithParentPointer* getLeft()
	{
		return left;
	}

	//Obtine subarborele drept
	BinarySearchTreeWithParentPointer* getRight()
	{
		return right;
	}

	//Obtine cheia din nodul curent
	T getData() 
	{
		return data;
	}

	//Supraincarcarea operatorului de atribuire, permite copierea unui arbore binar intr-un altul
	BinarySearchTreeWithParentPointer* operator = (BinarySearchTreeWithParentPointer* bst);

	//Insereaza o noua cheie in arbore, prin utilizarea pointer-ului suplimentar
	BinarySearchTreeWithParentPointer* insert(T const& val);

	//Afiseaza arborele binar de cautare ca rezultat in urma parcuergerii inordine
	void displayInOrder();

	//Construieste arborele binar de cautare
	BinarySearchTreeWithParentPointer<T>* buildBinaryTreeWithParentPointers();

	//Elibereaza memoria
	void Clear();

	//Parcurge arborele binar de cautare cu pointer suplimentar, folosind indici ai legaturii curente
	void treeCrossing(unsigned int rIdx, unsigned int lIdx);

};

//Supraincarcarea operatorului de atribuire, permite copierea unui arbore binar intr-un altul
template <class T>
BinarySearchTreeWithParentPointer<T>* BinarySearchTreeWithParentPointer<T>::operator=(BinarySearchTreeWithParentPointer<T>* bst)
{
	this->data = bst->data;
	this->left = bst->left;
	this->right = bst->right;
	this->parent = bst->parent;

	return this;
}

//Insereaza o noua cheie in arbore, prin utilizarea pointer-ului suplimentar
template<class T>
BinarySearchTreeWithParentPointer<T>* BinarySearchTreeWithParentPointer<T> :: insert(T const& val)
{
	BinarySearchTreeWithParentPointer<T>* copy = this;
	//Daca arborele este vid, se returneaza un nou nod
	if (copy==nullptr) return new BinarySearchTreeWithParentPointer<T>(val);

	//Recursivitate pentru constructia arborelui
	if (val < copy->data) {
		BinarySearchTreeWithParentPointer<T>* leftChild = copy->left->insert(val);
		copy->left = leftChild;
		leftChild->parent = copy;
	}
	else if(val>copy->data)
	{
		BinarySearchTreeWithParentPointer<T>* rightChild = copy->right->insert(val);
		copy->right = rightChild;
		rightChild->parent = copy;
	}

	//Returnam nodul rezultat
	return copy;

}

//Afiseaza arborele binar de cautare ca rezultat in urma parcuergerii inordine
template <class T>
void BinarySearchTreeWithParentPointer<T>::displayInOrder()
{
	BinarySearchTreeWithParentPointer<T>* copy = this;
	if (copy != nullptr) {
		this->left->displayInOrder();
		std::cout << data << "\t";
		this->right->displayInOrder();
	}

}

//Elibereaza memoria ocupata de un arbore binar de cautare
template <class T>
void BinarySearchTreeWithParentPointer<T>::Clear()
{
	if (left != nullptr) {
		left->Clear();
		delete left;
	}
	if (right != nullptr)
	{
		right->Clear();
		delete right;
	}
	//Reinitializare
	left = right = nullptr;
	parent = nullptr;
}

//Construieste arborele binar de cautare
template <class T>
BinarySearchTreeWithParentPointer<T>* BinarySearchTreeWithParentPointer<T>::buildBinaryTreeWithParentPointers()
{
	BinarySearchTreeWithParentPointer<T>* copy = this;

	//Sterge continutul arborelui in cazul in care acesta deja a fost populat anterior cu elemente.
	if (copy != nullptr) Clear();
	int nodes;
	T current;

	//Primul nod (radacina)
	std::cout << "Cate noduri?"; std::cin >> nodes;
	std::cout << "Nodul 1: "; std::cin >> current;
	copy = new BinarySearchTreeWithParentPointer<T>(current);

	//Restul de n-1 noduri
	for (int i = 2; i <= nodes; i++)
	{
		std::cout << "Nodul " << i + 1 << ": "; std::cin >> current;
		copy->insert(current);
	}
	return copy;
}

//Parcurge arborele binar de cautare cu pointer suplimentar in preordine, folosind indici ai legaturii curente
template <class T>
void BinarySearchTreeWithParentPointer<T>::treeCrossing(unsigned rIdx, unsigned lIdx)
{
	//Subarborele stang
	std::cout << data << '\t';
	if (lIdx == 0)
		if (left != nullptr)
			left->treeCrossing(0,lIdx);

	//Subarborele drept
	if (rIdx == 0)
		if (right != nullptr)
			right->treeCrossing(0, 1);

	if (rIdx == 1 && lIdx == 1 && parent != nullptr)
		parent->treeCrossing(0, 0);
}




