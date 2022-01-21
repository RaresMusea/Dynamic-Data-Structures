//Fisier header LinkedListPolinom.h->Utilizeaza clasa Term si implementarea listei simple inlantuite sortate  (clasa SortedLinkedList) pentru a implementa clasa Polinom alaturi de toate operatiile cu aceste structuri


#pragma once
#include "Term.h"
#include "SortedLinkedList.h"

//Clasa generica Polinom
template<class T>
class Polynomial
{

	SortedLinkedList<Term<T>> list;
	unsigned int degree;

public:

	//Constructor implicit:seteaza suportul polinomului (lista simplu inlantuita sortata, cat si gradul polinomului ca fiind nule)
	Polynomial() :list(), degree(0){}

	//Constructor de initializare, initializeaza polinomul cu un singur termen
	explicit Polynomial (Term<T> const& t) : degree(t.grade)
	{
		list.addValue(Term<T>(t.coef, t.grade));
	}

	//Constructor de copiere, copiaza variabilele membre ale polinomului-parametru P, in instanta curenta a clasei
	Polynomial (Polynomial<T> const& P):degree(P.degree),list(P.list){}

	//Destructorul, apeleaza metoda Destroy, a clasei SortedLinkedList, care la randul sau apeleza metoda Destroy din clasa de baza (LinkedList)
	~Polynomial()
	{
		list.Destroy();
		degree = 0;
	}

	unsigned int getDegree() { return degree; }

	SortedLinkedList<Term<T>>getList() { return list; }

	//Metoda care verifica daca un polinom are gradul si coeficientul nul
	bool isNull();

	//Adauga un termen la polinom
	void addTerm(Term<T> const& t);


	ListItem<Term<T>>* find(Term<T> const& val);

	//Elimina un termen din polinomul curent
	void removeTerm(Term<T>& t);

	//Adauga un termen in polinom prin specificarea perechii (coeficient, grad)
	void addByValue(T coeff, unsigned int grade);

	//Elimina un termen din polinom prin specificarea perechii (coeficient, grad)
	void removeByValue(T coeff, unsigned int grade);

	//Calculeaza derivata unui polinom
	Polynomial<T> polyDer();

	//Calculeaza si afiseaza intergrala unei functii polinomiale
	void polyIntegral();

	//Evalueaza functia intr-un punct si returneaza valoarea expresiei evaluate
	T eval(T const& x);

	//Obtine radacinile polinomului curent
	void getRoots();

	//Supraincarcari ale operatorului de atribuire:

	//Egaleaza un polinom polinom cu un monom
	Polynomial<T>& operator= (Term<T> const& t);

	//Copiaza un polinom in alt polinom
	Polynomial<T>& operator = (Polynomial<T> const& p);

	//Supraincarcarea operatorului de insumare

	//Calculeaza suma a doua polinomae
	Polynomial<T> operator + (Polynomial<T> p);

	//Supraincarcarea operatorului de scadere

	//Calculeaza diferenta a doua polinomae
	Polynomial<T> operator - (Polynomial<T> p);

	//Supraincarcari ale operatorului de inmultire

	//Calculeaza produsul a 2 polinoame
	Polynomial<T> operator * (Polynomial<T> p);

	//Calculeaza produsul dintre un polinom si un scalar
	Polynomial<T> operator * (T const& scalar);

	//Supraincarcarea operatorului de sciere in fluxul de intrare permite citirea de la tastatura a unui polinom
	friend istream& operator >> (istream& istr, Polynomial<T>& p) {

		unsigned int deg;
		T coefficient;


		cout << "Care este gradul polinomului? ";
		istr >> deg;
		p.degree = deg;

		for (int i = 0; i <= deg; i++) {
			cout << "Termenul de grad " << i << ":\n";
			cout << "Coeficient: "; istr >> coefficient;
			p.addByValue(coefficient, i);
		}

		//Eliminam elementele cu coeficientul 0

		if (p.list.getTail()->data.coef == 0 && p.list.getCount() > 1) {
			p.list.removeValue(p.list.getTail()->data);
			p.list.setCount(p.list.getCount()-1);
			//	p.degree = p.data[p.data.getSize() - 1].grade;
			//}
		}
		return istr;
	}

	//Supraincarcarea operatorului de scriere in fluxul de iesire, permite afisarea pe ecran a expresiei unui polinom
	friend ostream& operator << (ostream& ostr, Polynomial p)
	{
		if(p.isNull())
		{
			ostr << "Polinomul este nul!\n";
			return ostr;
		}

		unsigned int isFirst = 1;
		for (ListItem<Term<T>>*ptr = p.list.getHead(); ptr!=nullptr; ptr=ptr->next)
		{
			if (ptr->data.coef> 0)
				ostr<< ((isFirst) ? "" : "+");

			if (ptr->data.grade == 0)
				ostr << ptr->data.coef;
			else {
				if (ptr->data.coef == 1.0)
					ostr<< "X^" << ptr->data.grade;
				else {
					if (ptr->data.coef == -1.0)
						ostr<< "-X^" << ptr->data.grade;
					else
						ostr << ptr->data.coef << "X^" << ptr->data.grade;
				}
			}
			isFirst = 0;
		}

		ostr << '\n';

		return ostr;
	}

private:
	//Metoda privata utilizata pentru afisarea valorii integralei unei functii polinomiale
	void displayIntegralResult();

};

//Metoda care verifica daca un polinom are gradul si coeficientul nul
template <class T>
bool Polynomial<T>::isNull()
{
	return (degree == 0 && list.getHead()==nullptr);
}

//Metoda care cauta un termen in polinom si returneaza adresa nodului in cazul in care termenul se afla in polinom, respectiv nullptr in caz contrar.
template <class T>
ListItem<Term<T>>* Polynomial<T>::find(Term<T> const& val)
{
	ListItem<Term<T>>* pointer = list.getHead();
	while (pointer != nullptr && pointer->data!=val)
		pointer = pointer->next;
	return pointer;
}


//Adauga un termen in polinom
template <class T>
void Polynomial<T>::addTerm(Term<T> const& t)
{
	auto ptr=this->find(t);

	//Termenul nu s-a regasit in polinom
	if (ptr == nullptr) {
		list.addValue(t);
		degree = (degree < t.grade) ? t.grade : degree;
	}
	//Termenul a fost regasit in polinom
	else {
		//Term<T>& current = data[position];
		Term<T>&current = ptr->data;
		T sum = current.coef+t.coef;

		//Eliminare termen
		if (sum == 0.0) {
			list.removeValue(current);
			if (list.getCount() > 0)
				degree = list.getFirst().grade;
		}
		else
			current.coef = sum;
	}

	//Nu mai sunt termeni
	if (list.getCount() == 0) {
		list.Destroy();
		degree = 0;
	}

	else
	{
		const Term<T> t = list.getHead()->data;
		degree = t.grade;
	}
}

//Elimina un termen din polinomul curent
template <class T>
void Polynomial<T>::removeTerm(Term<T>& t)
{
	t.coef = -t.coef;
	addTerm(t);
}

//Adauga un termen in polinom prin specificarea perechii (coeficient, grad)
template <class T>
void Polynomial<T>::addByValue(T coeff, unsigned grade)
{
	addTerm(Term<T>(coeff, grade));
}

//Elimina un termen din polinom prin specificarea perechii (coeficient, grad)
template <class T>
void Polynomial<T>::removeByValue(T coeff, unsigned grade)
{
	Term<T> term(-coeff, grade);
	addTerm(term);
}

//Egaleaza un polinom cu un monom
template <class T>
Polynomial<T>& Polynomial<T>::operator=(Term<T> const& t)
{
	(*this) = Polynomial(t);
	return *this;
}

//Copiaza un polinom in alt polinom
template <class T>
Polynomial<T>& Polynomial<T>::operator=(Polynomial<T> const& p)
{
	list = p.list;
	degree = p.degree;

	return *this;
}

//Calculeaza suma a doua polinoame
template <class T>
Polynomial<T> Polynomial<T>::operator+ (Polynomial<T> p)
{
	//Copie a obiectului curent
	Polynomial<T>copy =*this;
	for (ListItem<Term<T>>* ptr = p.list.getHead(); ptr != nullptr; ptr = ptr->next)
		copy.addTerm(ptr->data);

	return copy;
}

//Calculeaza diferenta a doua polinoame
template <class T>
Polynomial<T> Polynomial<T>::operator-(Polynomial<T> p)
{
	//Copie a obiectului curent
	Polynomial<T> copy = *this;
	for(ListItem<Term<T>>*ptr=p.list.getHead();ptr!=nullptr;ptr=ptr->next)
	{
		copy.removeTerm(ptr->data);
	}

	return copy;

}

//Calculeaza produsul a doua polinoame
template <class T>
Polynomial<T> Polynomial<T>::operator*(Polynomial<T> p)
{
	//Posibilitatea existentei unui polinom nul->rezultatul inmultirii:tot un polinom nul
	if(p.isNull() || this->isNull())
	{
		Polynomial<T>result;
		return result;
	}

	//Cazul contrar:
	Polynomial<T>copy = *this;
	Polynomial<T>result;
	for (ListItem<Term<T>>*i =copy.list.getHead() ; i!=nullptr; i=i->next) {
		for (ListItem<Term<T>> *j =p.list.getHead(); j!=nullptr; j=j->next) {
			T coef = i->data.coef * j->data.coef;
			unsigned int grade = i->data.grade + j->data.grade;
			
			result.addByValue(coef, grade);
		}
	}
	return result;
}

//Inmulteste un polinom cu un scalar/constanta
template <class T>
Polynomial<T> Polynomial<T>::operator*(T const& scalar)
{
	Polynomial<T>copy = *this;

	for(ListItem<Term<T>>*ptr=copy.list.getHead();ptr!=nullptr;ptr=ptr->next)
	{
		T coef = ptr->data.coef * scalar;
		ptr->data.coef = coef;
	}

	return copy;
}

//Calculeaza derivata polinomului curent
template <class T>
Polynomial<T> Polynomial<T>::polyDer()
{
	Polynomial<T>copy = *this;
	for (ListItem<Term<T>>* ptr = copy.list.getHead(); ptr != nullptr; ptr = ptr->next)
	{
			ptr->data.coef = ptr->data.coef * ptr->data.grade;
			ptr->data.grade--;
	}

	//Eliminam ultimul element, deoarece prin derivare, constantele devin 0, iar conform conventiei, ultimul element este de grad 0
	//Daca gradul unui termen are valoarea 0 si se decrementeaza, valoarea sa in urma decrementarii va fi 4294967295, intrucat vorbim de stocare intr-o variabila de tipul INT_MAX
	if(copy.list.getTail()->data.grade==4294967295)
	copy.list.removeFromTail();

	return copy;
}

//Calculeaza integrala unei functii polinomiale
template <class T>
void Polynomial<T>::polyIntegral()
{
	Polynomial<T>copy = *this;
	Polynomial<T>result;

	//Integrarea unei valori constante
	if (copy.list.getCount() == 1 && copy.list.getHead()->data.grade == 0) {
		result.addByValue(copy.list.getHead()->data.coef, 1);
		cout << "Rezultat in urma integrarii functiei:\n";
		cout << result << " +C.\n";
		return;
	}


	//Integrarea unei functii polinomiale
	for(ListItem<Term<T>>*ptr=copy.list.getHead();ptr!=nullptr;ptr=ptr->next)
		ptr->data.grade = ptr->data.grade+ 1;

	//Utilizam metoda privata displayIntegralResult pentru a afisa rezultatele in urma integrarii
	copy.displayIntegralResult();

	
}


//Metoda utilitara, utilizata pentru afisarea rezultatului in urma integrarii a unei functii polinomiale
template <class T>
void Polynomial<T>::displayIntegralResult()
{
	Polynomial<T>copy = (*this);
	cout << "In urma integrarii functiei, s-a obtinut:\n";

	unsigned int isFirst = 1;
	for (ListItem<Term<T>>* ptr = copy.list.getHead(); ptr != nullptr; ptr = ptr->next)
	{
		if (ptr->data.coef > 0)
			cout<< ((isFirst) ? "" : "+");

		if (ptr->data.grade == 0)
			cout << ptr->data.coef;
		else {
			if (ptr->data.coef == 1.0)
				cout<< "X^" << ptr->data.grade<<"/"<<ptr->data.grade;
			else {
				if (ptr->data.coef == -1.0)
					cout<< "-X^" << ptr->data.grade<<"/"<<ptr->data.grade;
				else
					cout << ptr->data.coef << "X^" << ptr->data.grade<<"/"<<ptr->data.grade;
			}
		}
		isFirst = 0;

	}
	cout << " +C.\n";
}

//Evalueaza polinomul in punctul x
template <class T>
T Polynomial<T>::eval(T const& x)
{
	Polynomial<T>copy = *this;
	double result = 0.0;
	for(ListItem<Term<T>>*ptr=copy.list.getHead();ptr!=nullptr;ptr=ptr->next)
	{
		result += ptr->data.coef * pow(x, ptr->data.grade);
	}

	return result;
}

//Obtine radacinile polinomului curent
template <class T>
void Polynomial<T>::getRoots()
{
	cout << "Radacinile polinomului: \n";
	Polynomial p = *this;
	int roots = 0;
	T numberOfRoots = abs(p.getList().getTail()->getData().coef);
	for (int i = 1; i <= numberOfRoots; i++) {
		if (numberOfRoots % i == 0) {
			if (p.eval(i) == 0) {
				cout << i << "\t";
				roots++;
			}
			if (p.eval(-i) == 0) {
				cout << -i << "\t";
				roots++;
			}
		}
	}
	if (roots == 0)
		cout << "Nu s-au gasit radacini!\n";
}


