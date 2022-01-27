#include "BinarySearchTreeWithParentPointer.h"
using namespace std;
int main()
{
	BinarySearchTreeWithParentPointer<int>*bst=new BinarySearchTreeWithParentPointer<int>;
	bst=bst->buildBinaryTreeWithParentPointers();

	//bst->displayInOrder();
	bst->treeCrossing(0,0);
	return 0;
	
}