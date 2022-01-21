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

#pragma endregion