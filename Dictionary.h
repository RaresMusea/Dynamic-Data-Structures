//Fisier Dictionary.h->Contine clasa Dictionary, ce implementeaza o structura de date de tip pereche, in care se vor stoca valori de tipul cuvant-traducere, intocmai ca in cazul unui dictionar
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Dictionary
{
private:
	//Cuvantul
	string word;
	//Traducerea acestuia
	string translation;

public:
	//Constructor implicit
	Dictionary() = default;

	//Constructor inline de initializare:initializeaza variabilele membru ale instantei clasei cu cei 3 parametrii
	Dictionary(string w, string tr) : word(move(w)), translation(move(tr)){}

	//Constructor de copiere
	Dictionary(const Dictionary& d) = default;

	//Obtine cuvantul din dictionar
	string getWord()const 
	{
		return word;
	}

	//Obtine traducerea cuvantului din dictionar
	string getTranslation()const
	{
		return translation;
	}

	//Seteaza cuvantul
	void setWord(const string& w)
	{
		this->word = w;
	}

	//Seteaza traducerea cuvantului
	void setTranslation(const string& tr)
	{
		this->translation = tr;
	}

	//Supraincaracrea operatorului de scriere in fluxul de intrare, permite citirea de la tastatura a unei intrari din dictionar
	friend istream& operator >>(istream& istr, Dictionary& dict)
	{
		cin.ignore();
		cout << "Introduceti cuvantul in limba romana: ";
		string word;
		getline(istr, word);
		dict.setWord(word);
		cin.ignore();
		cout << "Introduceti traducerea cuvantului " << dict.getWord() << " in limba engleza : ";
		std::getline(istr, word);
		dict.setTranslation(word);
		return istr;
	}

	//Supraincarcarea operatorului de scriere in fluxul de iesire, permite afisarea pe ecran a intrarii din dictionar
	friend ostream& operator <<(ostream& ostr, Dictionary dict)
	{
		ostr << dict.getWord() << "-" << dict.getTranslation();
		ostr << '\n';
		return ostr;
	}

	//Supraincarcari de operatori, ce vor fi utilizati pentru amplasarea intrarilor din dictionar in arborele binar de cautare, cat si pentru compararea, efectuata intre nodurile de tip Dictionary ale arborelui, la inserare, respectiv cautare.

	//Supraincarcarea operatorului >, permite compararea a 2 intrari in romana din dictionar din punct de vedere lexicografic
	bool operator >(Dictionary const& dict)const 
	{
		return this->getWord() > dict.getWord() || this->getTranslation()>dict.getTranslation();
	}

	//Supraincarcarea operatorului <, permite compararea a 2 intrari in romana din dictionar din punct de vedere lexicografic
	bool operator <(Dictionary const& dict)const
	{
		return (this->getWord() < dict.getWord() || this->getTranslation()<dict.getTranslation());
	}

	//Supraincarcarea operatorului de egalitate, permite comparararea a 2 intrari in limba romana din dictionar, din punct de vedere lexicografic, cat si verificarea ca acestea sunt identice
	bool operator ==(Dictionary const& dict)const
	{
		return this->getWord() == dict.getWord() || this->getTranslation()==dict.getTranslation();
	}
};
