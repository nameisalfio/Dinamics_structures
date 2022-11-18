#include<iostream>
#include<queue>
using namespace std;

#include"RBTree.h"

int main()
{
	RBTree<int> tree;
	tree.insertKey(50);
	tree.insertKey(20);
	tree.insertKey(40);
	tree.insertKey(60);
	tree.insertKey(70);


	cout << "\nVisita in order: " << endl;
	tree.inOrder();

	cout << "\nVisita pre order: " << endl;
	tree.preOrder();

	cout << "\nVisita post order: " << endl;
	tree.postOrder();
}