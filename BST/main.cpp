#include<iostream>
using namespace std;

#include "BST.h"

int main(){
	
	BST<int> bst;
/*
	try
	{
		bst.min();
	}
	catch(const char*) //se dovessi trovare un'eccezione const char* nel blocco "try"
	{
		cout << "\nEmpty BST!" << endl;
	}
*/
	bst.insert(10);
	bst.insert(4);
	bst.insert(5);
	bst.insert(18);
	bst.insert(12);
	bst.insert(11);
	bst.insert(3);

	cout << "\nVisita in order: " << endl;
	bst.in_order();

	cout << "\nRadice: " << *bst.getRoot() << endl;
	cout << "\nMax:\n" << *bst.max() << endl;
	cout << "\nMin:\n" << *bst.min() << endl;

	cout << "\nSuccessore di " << *bst.getRoot() << *bst.successor(bst.getRoot()) << endl;
	cout << "\nPredecessore di " << *bst.getRoot() << *bst.predecessor(bst.getRoot()) << endl;

	cout << "\nNodo 3 : \t" << *bst.search(3) << endl;
	cout << "\nNodo 8 : \t" << (bst.search(8) ? "Found" : "Not found !") << endl;

	cout << "\nDistanza dal successore di 10 : " << bst.from_successor(10) << endl;
	cout << "\nDistanza tra 10 e 3 : " << bst.between_nodes(10, 3) << endl;

	cout << bst << endl;

/*
	cout << "\nElimino tutti i nodi al di sopra di 5: " << endl;
	bst.remove_above(5);
	cout << bst << endl;
*/
}