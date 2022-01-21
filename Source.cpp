//#include "DoubleLinkedList.h"
//
////Fucntia Link, preia un nod al unei liste dublu inlantuite si realizeaza operatia binara XOR (sau exclusiv), astfel:
////daca exista nod anterior si urmator (in raport cu node), returneaza 1
////In orice alt caz caz, returneaza 0.
//template <class T>
//int Link(DoubleLinkedListItem<T>* node)
//{
//	const int left = node->getPrevious() == nullptr ? 0 : 1;
//	const int right = node->getNext() == nullptr ? 0 : 1;
//
//	return left ^ right;
//}
//
////Face apel la functia Link, pentru a parcurge lista dublu inlantuita de la stanga spre dreapta
//template <class T>
//void leftToRight(DoubleLinkedList<T> list)
//{
//	DoubleLinkedListItem<T>* ptr = list.getHead();
//	if (list.isEmpty())
//	{
//		cout << "Lista este goala!\n";
//		return;
//	}
//
//	//Primul nod (head) va avea adresa previous nula
//	if (Link(ptr))
//	{
//		cout << ptr->getData() << '\t';
//		ptr = ptr->getNext();
//	}
//
//	//Restul nodurilor cuprinse intre head si tail vor avea atat adresele next si previous nenule
//	while (Link(ptr) == 0)
//	{
//		cout << ptr->getData() << '\t';
//		ptr = ptr->getNext();
//	}
//
//	//Ultimul nod (tail) va avea adresa next nula
//	if (Link(ptr))
//		cout << ptr->getData() << '\t';
//
//	cout << '\n';
//}
//
////Face apel la functia Link, pentru a parcurge lista dublu inlantuita de la dreapta spre stanga
//template <class T>
//void rightToLeft(DoubleLinkedList<T> list)
//{
//	DoubleLinkedListItem<T>* ptr = list.getTail();
//	if (list.isEmpty())
//	{
//		cout << "Lista este goala!\n";
//		return;
//	}
//
//	//Primul nod (tail) va avea adresa previous nula
//	if (Link(ptr))
//	{
//		cout << ptr->getData() << '\t';
//		ptr = ptr->getPrevious();
//	}
//
//	//Restul nodurilor cuprinse intre tail si head vor avea atat adresele next cat si previous nenule
//	while (Link(ptr) == 0)
//	{
//		cout << ptr->getData() << '\t';
//		ptr = ptr->getPrevious();
//	}
//
//	//Ultimul nod (head) va avea adresa next nula
//	if (Link(ptr))
//		cout << ptr->getData() << '\t';
//
//	cout << '\n';
//}
//
//
//int main()
//{
//	DoubleLinkedList<int> dl;
//	dl.addLast(2);
//	dl.addLast(3);
//	dl.addLast(4);
//	leftToRight(dl);
//	rightToLeft(dl);
//	return 0;
//}
//#include "LinkedListPolinom.h"
//
//template<class T>
//double* quadraticEquationSolver(Polynomial<T>p)
//{
//	double* result = new double[2];
//	if (p.getDegree() == 2) {
//		SortedLinkedList<Term<T>>list = p.getList();
//		Term<T>a = list.getHead()->getData();
//		Term<T>b = list.getHead()->getNext()->getData();
//		Term<T>c = list.getTail()->getData();
//
//		double delta = b.coef * b.coef - 4 * (a.coef * c.coef);
//		if (delta == 0) {
//			*result = -b.coef / (double)(2 * a.coef);
//			return result;
//		}
//		if (delta > 0) {
//			*result = (-b.coef + sqrt(delta)) / (double)(2 * a.coef);
//			*(result + 1) = (-b.coef - sqrt(delta)) / (double)(2 * a.coef);
//			return result;
//		}
//	}
//	else
//	{
//		return result;
//	}
//
//}
//
//int main()
//{
//	Polynomial<double>x;
//	double* res = new double[2];
//	cin >> x;
//	cout << x;
//	res = quadraticEquationSolver(x);
//	cout << *res << "\t" << *(res + 1);
//	cout << x.eval(*res);
//	cout << "\n" << x.eval(*(res + 1));
//	return 0;
//}

#include "DoubleLinkedList.h"
int main()
{
	DoubleLinkedList<int>dl;
	dl.addLast(1);
	dl.addLast(2);
	dl.addLast(3);
	dl.addLast(5);

	//Obtinem cel mai din stanga element
	DoubleLinkedListItem<int>* ptr = dl.getHead();
	if (!dl.isEmpty()) {
		if (ptr->getLink() == 1) {
			cout << ptr->getData() << "\t";
			ptr = ptr->getNext();
		}
		while (ptr->getLink() == 0) {
			cout << ptr->getData() << "\t";
			ptr = ptr->getNext();
		}
		if (ptr->getLink() == 0)
			cout << ptr->getData();
	}
	else
		cout << "Lista este vida!\n";
	return 0;

}