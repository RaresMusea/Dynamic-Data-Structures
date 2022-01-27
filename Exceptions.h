//Fisier Exceptions.h->Contine definitii ale claselor ce definesc exceptii specifice structurilor de date dinamice
#pragma once
#include <iostream>
#include <exception>


class ListException:public std::exception
{
public:

	void handle(std::string const &ex) throw()
	{
		std::cout << ex << '\n';
	}
};


//Defineste clasa StackException, care va fi utilizata pentru a trata toate exceptiile ce pot aparea in clasa StackArray
class StackException :public std::exception {

public:
	void handle(std::string error) throw() {
		//Afiseaza mesajul de eroare
		std::cout << error << '\n';
	}
};


//Defineste clasa QueueException, care va fi utilizata pentru a trata toate exceptiile ce pot aparea in clasa QueueArray.
//Intrucat clasa va avea o singura metoda, identica cu cea a clasei de mai sus, clasa QueueException mosteneste clasa StackException
class QueueException :public StackException {};

//Defineste clasa PolishNotationException, care va fi utilizata pentru a trata toate exceptiile ce pot aparea in clasa Parser.
//Intrucat clasa va avea o singura metoda, identica cu cea a clasei de mai sus, clasa PolishNotationException mosteneste clasa StackException




#pragma endregion