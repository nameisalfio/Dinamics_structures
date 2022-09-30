#include<iostream>
using namespace std;

#include "RBTree.h"

int main(){
	
	RBTree<int> tree(true);

	tree.insert(13);
	tree.insert(8);
	tree.insert(17);
	tree.insert(1);
	tree.insert(11);
	tree.insert(15);
	tree.insert(25);
	tree.insert(6);
	tree.insert(22);
	tree.insert(27);

	cout << "\nVisita in order: " << endl;
	tree.inOrder();

}

