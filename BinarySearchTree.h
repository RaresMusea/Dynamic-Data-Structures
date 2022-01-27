//Fisier BinarySearchTree.h, contine clasa BinarySearchTree, ce implementeaza conceptul de arbore de cautare binara (ABC), pornind de la conceptul de Container, o interfata implementata in fisierul Container.h
#pragma once
#include "Container.h"
#include <stdexcept>
#include <iostream>

//Clasa generica BinarySearchTree, implementeaza conceptul de arbore binar de cautare
template <class T>
class BinarySearchTree:public Container
{
private:

	T data;
	//Subarborele stang
	BinarySearchTree<T>* left;
	//Subarborele drept
	BinarySearchTree<T>* right;



public:
	//Constructor implicit
	BinarySearchTree() { count = 0;left = nullptr; right = nullptr; }

	//Constructor de initializare, initializeaza arborele binar de cautare cu o radacina
	BinarySearchTree(T const& root) :data(root), left(nullptr), right(nullptr) { count++;}

	//Constructor de copiere, copiaza un alt arbore binar de cautare in instanta curenta a clasei
	BinarySearchTree(BinarySearchTree<T> const& bst) {

		this->data = bst.data;
		this->left = bst.left;
		this->right = bst.right;
		this->count = 1 + (bst.left != nullptr ? bst.left->count : 0) + (bst.right != nullptr ? bst.right->count : 0);

	}

	//Destructorul, apeleaza metoda Clear si suprapune destructorul interfetei Container
	~BinarySearchTree() override { /*Clear();*/ }

	//Elibereaza memoria ocupata de un arbore binar de cautare
	void Clear();

	//Insereaza o valoare in arborele binar de cautare
	BinarySearchTree<T>* insert(T const& val);

	//Verifica daca arborele binar de cautare este sau nu vid
	bool isEmpty() const override;

	//Obtine numarul de elemente din arborele binar de cautare
	unsigned getCount() const override;

	//Obtine informatia stocata in nodul curent
	T& getData();

	//Afiseaza arborele binar de cautare ca rezultat in urma parcuergerii inordine
	void displayInOrder();

	//Cauta o valoare intr-un arbore binar de cautare 
	BinarySearchTree* find(T const& val);

	//Metoda utilitara, ce va fi utilizata pentru obtinerea cheii (a nodului) cu valoarea minima
	BinarySearchTree* getMinimumValue();

	//Sterge un nod din arborele binar de cautare dupa o valoare data astfel:
	//1) In cazul in care nodul ce urmeaza sa fie sters are ambii parinti (subarbori) nevizi, se detemina predecesorul nodului de sters, predecsor raportat la traversarea in inordine, prin parcurgerea la fiul stang si apoi cat se poate de in dreapta.Acesta va fi amplasat in locul nodului curent ce initial trebuia sters
	//2) Daca nodul de sters este o frunza, se elimina pur si simplu din arbore
	//3) Daca nodul are un singur subarbore descendent, se repozitioneaza descendentul
	BinarySearchTree* deleteNode(T value);

	//Obtine subarborele stang
	BinarySearchTree* getLeft() { return left; }

	//Obtine subarborele drept
	BinarySearchTree* getRight() { return right; }

private:
	//Verifica daca arborele binar de cautare este sau nu plin. Intrucat structura de date este implementata dinamic, aceasta metoda va fi setata drept private si va returna mereu valoarea false
	bool isFull() const override { return false; }

};

//Insereaza o valoare in arborele binar de cautare
template <class T>
BinarySearchTree<T>* BinarySearchTree<T>::insert(T const& val)
{
	if (!this) {
		return new BinarySearchTree<T>(val);
	}

	if(val>this->data)
	{
		count++;
		this->right=this->right->insert(val);
	}

	else
	{
		count++;
		this->left=this->left->insert(val);
	}

	return this;
}

//Obtine numarul de elemente din arborele binar de cautare
template <class T>
unsigned BinarySearchTree<T>::getCount() const
{
	return count;
}

//Afiseaza arborele binar de cautare ca rezultat in urma parcuergerii inordine
template <class T>
void BinarySearchTree<T>::displayInOrder()
{
	BinarySearchTree<T>* copy = this;
	if (copy != nullptr) {
		this->left->displayInOrder();
		std::cout << data << "\t";
		this->right->displayInOrder();
	}

}

//Verifica daca arborele binar de cautare este sau nu vid
template <class T>
bool BinarySearchTree<T>::isEmpty() const
{
	return count == 0;
}

//Cauta o valoare intr-un arbore binar de cautare
template <class T>
BinarySearchTree<T>* BinarySearchTree<T>::find(T const& val)
{
	if (this == nullptr)
	{
		return nullptr;
	}

	if (this->data == val)
		return this;

	//Apeluri recursive
	if (val > this->data)
		return this->right->find(val);

	return this->left->find(val);

}

//Obtine informatia stocata in nodul curent
template <class T>
T& BinarySearchTree<T>::getData()
{
	return data;
}

//Elibereaza memoria ocupata de un arbore binar de cautare
template <class T>
void BinarySearchTree<T>::Clear()
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
	count = 0;

}

//Metoda utilitara, ce va fi utilizata pentru obtinerea cheii (a nodului) cu valoarea minima
template <class T>
BinarySearchTree<T>* BinarySearchTree<T>::getMinimumValue()
{
	BinarySearchTree<T>* current(this);
	while (current->left != nullptr)
		current = current->left;

	return current;
		
}

//Sterge un nod din arborele binar de cautare dupa o valoare data astfel:
//1) In cazul in care nodul ce urmeaza sa fie sters are ambii parinti (subarbori) nevizi, se detemina predecesorul nodului de sters, predecsor raportat la traversarea in inordine, prin parcurgerea la fiul stang si apoi cat se poate de in dreapta.Acesta va fi amplasat in locul nodului curent ce initial trebuia sters
//2) Daca nodul de sters este o frunza, se elimina pur si simplu din arbore
//3) Daca nodul are un singur subarbore descendent, se repozitioneaza descendentul
template <class T>
BinarySearchTree<T>* BinarySearchTree<T>::deleteNode(T value)
{
	//Cazul de baza
	if (this == nullptr)
		return this;

	//In situatia in care nodul ce va urma a fi sters are o cheie ce este mai mica decat radacina , vom cauta nodul ce urmeaza a fi sters in stanga
	if (value < this->data) {
		this->left= this->left->deleteNode(value);
		return this;
	}

	//In situatia in care nodul ce va urma a fi sters are o cheie ce este mai mica decat radacina , vom cauta nodul ce urmeaza a fi sters in dreapta
	 if (value > this->data) {
		this->right=this->right->deleteNode(value);
		return this;
	 }

	//Ajungem in punctul in care radacina este nodul ce urmeaza a fi sters
	//Daca nodul are un singur descendent:

	if(this->left==nullptr)
	{
		BinarySearchTree<T>* aux = this->right;
		count--;
		delete this;
		return aux;
	}

	if(this->right==nullptr)
	{
		BinarySearchTree<T>* aux = this->left;
		delete this;
		return aux;
	}

	//Caz de tratat:nodul de eliminat contine atat subarborele stang cat si pe cel drept

	BinarySearchTree<T>* parent=this;
	//Determinam succeecesorul nodului de sters, conform parcurgerii in inordine
	BinarySearchTree<T>* successor = this->right;
	while(successor->left!=nullptr)
	{
		parent = successor;
		successor = successor->left;
	}

	if (parent != this)
		parent->left = successor->right;
	else
		parent->right = successor->right;

	//Copiem informatia stocata de succesor
	this->data = successor->data;
	delete successor;
	return this;
}









