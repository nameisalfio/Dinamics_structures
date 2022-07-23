#include<iostream>
using namespace std;

#include "BST.h"

int main(){
	
	BST<int> bst;

	try
	{
		bst.min();
	}
	catch(const char*) //se dovessi trovare un'eccezione const char* nel blocco "try"
	{
		cout << "\nEmpty BST!" << endl;
	}

	bst.insert(10);
	bst.insert(4);
	bst.insert(5);
	bst.insert(18);
	bst.insert(11);
	bst.insert(3);
	bst.insert(12);
/*
	cout << "\nVisita pre order: " << endl;
	bst.pre_order();

	cout << "\nVisita post order: " << endl;
	bst.post_order();
*/
	cout << "\nVisita in order: " << endl;
	bst.in_order();
/*
	cout << "\nMax:\n" << *bst.max() << endl;
	cout << "\nMin:\n" << *bst.min() << endl;

	cout << "\nSuccessore di " << *bst.get_root() << *bst.successor(bst.get_root()) << endl;
	cout << "\nPredecessore di " << *bst.get_root() << *bst.predecessor(bst.get_root()) << endl;

	cout << "\nNodo 3 : \t" << *bst.search(3) << endl;
	cout << "\nNodo 8 : \t" << (bst.search(8) ? "Found" : "Not found !") << endl;

	//Successore di una foglia
	cout << "\nSuccessore di " << *bst.get_root() << *bst.successor(bst.get_root()) << endl;
*/
	cout << "\nElimino il nodo 12" << endl;
	bst.remove(12);
	bst.in_order();

	cout << "\nElimino tutti i nodi al di sotto di 12: " << endl;
	bst.remove_below(12);
	cout << bst << endl;
/*
	cout << "\nElimino tutti i nodi al di sopra di 12: " << endl;
	bst.remove_above(12);
	cout << bst << endl;

	cout << "\nElimino tutti i nodi ricorrenti di 12: " << endl;
	bst.remove_equal(12);
	cout << bst << endl;
*/
}